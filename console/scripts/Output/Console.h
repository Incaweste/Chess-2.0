#pragma once

#include <algorithm>
#include <iostream>
#include <ranges>
#include <span>
#include <stdexcept>
#include <system_error>
#include <windows.h>
#undef RGB

#include "Vector2.h"
#include "TextBlock.h"

class Console
{
private:
    static inline const HANDLE OUTPUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
    static constexpr std::size_t MAX_WRITABLE_CHUNK_CHARS = 32 * 1024;
public:
    Console() = delete;

    static bool DoesThisFitInConsole(Vector2 size)
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        if (!GetConsoleScreenBufferInfo(OUTPUT_HANDLE, &info))
            return false;

        std::size_t consoleRowCnt = info.srWindow.Bottom - info.srWindow.Top + 1;
        std::size_t consoleColCnt = info.srWindow.Right - info.srWindow.Left + 1;

        return size.row <= consoleRowCnt && size.col <= consoleColCnt;
    }

    static void ResetCaret()
    {
        DrawWstring(L"\033[1;1H");
    }

    static void RefreshConsoleAfterCaret()
    {
        DrawWstring(L"\033[J");
    }

    static void RefreshConsole()
    {
        DrawWstring(L"\033[2J\033[3J");
        ResetCaret();
    }

    static void DrawTextBlocks(std::span<const TextBlock> squaredFilledTextBlocks)
    {
        auto notEmptyTextBlocks = squaredFilledTextBlocks | std::views::filter([](const TextBlock& value){
            return value.GetLinesCount() > 0; 
        });
        std::wstring result;

        result += GetInOneLine(squaredFilledTextBlocks);
        DrawWstring(result);
    }

    static void DrawWstring(std::wstring_view wst)
    {
        while (!wst.empty())
        {
            const DWORD charsCount = static_cast<DWORD>(std::min(wst.size(), MAX_WRITABLE_CHUNK_CHARS));
            DWORD writtenChars = 0;

            if (!WriteConsoleW(OUTPUT_HANDLE, wst.data(), charsCount, &writtenChars, nullptr))
                throw std::system_error(static_cast<int>(GetLastError()), std::system_category(), "WriteConsoleW");
            else if (writtenChars == 0)
                throw std::runtime_error("WriteConsoleW has written no characters");

            wst.remove_prefix(writtenChars);
        }
    }

private:
    static std::wstring GetInOneLine(std::ranges::forward_range auto&& notEmptyTextBlocks)
    {
        static TextBlock::Line resetLine = [](){
            TextBlock::Line rl;
            rl.ResetActiveColor(TextBlock::Line::ColorTarget::TEXT);
            rl.ResetActiveColor(TextBlock::Line::ColorTarget::BACKGROUND);
            return rl;
        }();
        static std::wstring_view resetColors = resetLine;

        std::size_t height = 0;
        std::size_t commonWidth = 0;
        std::size_t textBlocksCount = 0;

        for (const TextBlock& textBlock : notEmptyTextBlocks)
        {
            height = std::max(height, textBlock.GetLinesCount());
            commonWidth += textBlock.gapBefore + textBlock[0].GetWidth();
            ++textBlocksCount;
        }
        std::wstring result;
        result.reserve(height * commonWidth + height - 1 + (textBlocksCount * height + 1) * resetColors.size()); //must be dynamic
        result.append(resetColors);

        auto firstIt = notEmptyTextBlocks.begin();
        for (std::size_t y = 0; y < height; ++y)
        {
            if (y > 0)
                result += L'\n';
            for (std::size_t i = 0; i < textBlocksCount; ++i)
            {
                const TextBlock& textBlock = *(firstIt + i);    
                std::size_t linesCount = textBlock.GetLinesCount();
                if (linesCount == 0)
                    continue;

                result.append(textBlock.gapBefore, L' ');

                if (y < linesCount)
                {
                    result += static_cast<std::wstring_view>(textBlock[y]);
                    result.append(resetColors);
                }
                else
                    result.append(textBlock[0].GetWidth(), L' ');
            }
        }

        return result;
    }
};
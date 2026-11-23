#pragma once

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

struct TextBlock
{
public:
    enum class ColorTarget
    {
        TEXT,
        BACKGROUND
    };

    struct RGB;
    struct Color;
    class Line;
    
public:
    std::size_t gapBefore = 0;

private:
    std::vector<Line> _lines{};

public:
    constexpr TextBlock() noexcept = default;

    constexpr TextBlock(
        std::size_t linesCount, 
        std::size_t oneLineLength,
        const RGB* defaultTextColor, 
        const RGB* defaultBGColor, 
        bool areColorsAlreadySetted, 
        std::size_t gapBefore
    );

    constexpr TextBlock(
        std::size_t linesCount, 
        const RGB* defaultTextColor, 
        const RGB* defaultBGColor, 
        bool areColorsAlreadySetted, 
        std::size_t gapBefore
    );

    constexpr TextBlock(
        std::size_t linesCount, 
        std::size_t oneLineLength, 
        const RGB* defaultTextColor, 
        const RGB* defaultBGColor, 
        bool areColorsAlreadySetted
    );

    constexpr TextBlock(
        std::size_t linesCount, 
        const RGB* defaultTextColor, 
        const RGB* defaultBGColor, 
        bool areColorsAlreadySetted
    );

    constexpr TextBlock(std::size_t linesCount, std::size_t oneLineLength, std::size_t gapBefore);

    constexpr TextBlock(std::size_t linesCount, std::size_t oneLineLength);

    constexpr explicit TextBlock(std::size_t linesCount);

    constexpr Line& operator[](std::size_t index);
    constexpr const Line& operator[](std::size_t index) const;

    constexpr auto begin() const noexcept;
    constexpr auto end() const noexcept;
    constexpr auto begin() noexcept;
    constexpr auto end() noexcept;

    constexpr std::size_t GetLinesCount() const noexcept;
    constexpr void AddCharsForSeveralLines(
        std::size_t startIndex, 
        std::size_t linesCount, 
        std::size_t charsCount = 1, 
        wchar_t character = L' '
    );
    constexpr void AddCharsForAllLines(std::size_t charsCount = 1, wchar_t character = L' ');
    constexpr void AddLines(std::size_t count);
    constexpr void RemoveLines(std::size_t startIndex, std::size_t count = 1);
    constexpr void MergeWithTextBlock(const TextBlock& mergingLines, std::size_t startIndexInMain = 0);

    void SetActiveColorForSeveralLines(
        std::size_t startIndex, 
        std::size_t linesCount,
        ColorTarget target,
        const RGB* color
    );
    void SetActiveColorForAllLines(ColorTarget target, const RGB* color);
};

#include "RGB.inl"
#include "Color.inl"
#include "Line.inl"
#include "TextBlock.inl"
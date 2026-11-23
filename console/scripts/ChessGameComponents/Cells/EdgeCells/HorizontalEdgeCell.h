#pragma once

#include "BaseEdgeCell.h"
#include "CellsConfiguration.h"
#include "Utilits.h"

class HorizontalEdgeCell : public BaseEdgeCell<CellsConfiguration::BASE_WIDTH, CellsConfiguration::HORIZONTAL_EDGE_HEIGHT>
{
    static_assert(HEIGHT >= 2);
public:
    enum class Type{
        TOP,
        BOTTOM
    };
private:
    static constexpr std::size_t HALF_WIDTH = WIDTH / 2;
    const wchar_t MARKED_LETTER;
    const Type SIDE_TYPE;
    const std::size_t FILLED_LINE;
    const std::size_t MARKED_LINE;
public:
    constexpr HorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter, const RGB* cellColor, Type sideType) :     
        BaseEdgeCell{edgeChar, cellColor}, MARKED_LETTER{markedLetter}, SIDE_TYPE{sideType},
        FILLED_LINE{SIDE_TYPE == Type::TOP ? HEIGHT - 1 : 0}, MARKED_LINE{SIDE_TYPE == Type::TOP ? HEIGHT - 2 : 1}
    {   
    }
    constexpr HorizontalEdgeCell(wchar_t edgeChar, wchar_t markedLetter, Type sideType) : 
        HorizontalEdgeCell{edgeChar, markedLetter, nullptr, sideType}
    {
    }

    TextBlock BuildTextBlock(const TextBlock::RGB* outsideTextColor, const TextBlock::RGB* outsideBGColor) const override
    {
        TextBlock textBlock{HEIGHT, WIDTH, outsideTextColor, outsideBGColor, true};

        for (std::size_t i = 0; i < HEIGHT; ++i)
        {
            if (i == FILLED_LINE)
                AddEdgeChars(textBlock[i], WIDTH);
            else if (i == MARKED_LINE)
                AddOutsideLine(textBlock[i], std::wstring_view(&MARKED_LETTER, 1), HALF_WIDTH, HALF_WIDTH);
            else
                AddOutsideLine(textBlock[i], {}, WIDTH);
        }

        return textBlock;
    }
};
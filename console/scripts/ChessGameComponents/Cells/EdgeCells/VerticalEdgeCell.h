#pragma once

#include "BaseEdgeCell.h"
#include "CellsConfiguration.h"
#include "Utilits.h"

class VerticalEdgeCell : public BaseEdgeCell<CellsConfiguration::VERTICAL_EDGE_WIDTH, CellsConfiguration::BASE_HEIGHT>
{
    static_assert(WIDTH >= 2);
public:
    enum class Type
    {
        LEFT,
        RIGHT
    };
protected:
    static constexpr std::size_t LAST_COL = WIDTH - 1;
    static constexpr std::size_t MID_HEIGHT = HEIGHT / 2;
    const std::wstring MARKED_DIGIT;
    const std::size_t LAST_COL_TO_MARKED_ONE;
    const Type SIDE_TYPE;
public:
    VerticalEdgeCell(wchar_t edgeChar, std::size_t markedDigit, const RGB* cellColor, Type sideType) :
        BaseEdgeCell{edgeChar, cellColor}, MARKED_DIGIT{std::to_wstring(markedDigit)}, 
        LAST_COL_TO_MARKED_ONE{LAST_COL - MARKED_DIGIT.size()}, SIDE_TYPE{sideType}
    {
    }

    VerticalEdgeCell(wchar_t edgeChar, std::size_t markedDigit, Type sideType) : 
        VerticalEdgeCell{edgeChar, markedDigit, nullptr, sideType}
    {
    }

    TextBlock BuildTextBlock(const TextBlock::RGB* outsideTextColor, const TextBlock::RGB* outsideBGColor) const override
    {
        TextBlock textBlock{HEIGHT, WIDTH, outsideTextColor, outsideBGColor, true};

        for (std::size_t i = 0; i < HEIGHT; ++i)
        {
            if (SIDE_TYPE == Type::LEFT)
            {
                if (i == MID_HEIGHT)
                    AddOutsideLine(textBlock[i], MARKED_DIGIT, LAST_COL_TO_MARKED_ONE);
                else
                    AddOutsideLine(textBlock[i], {}, LAST_COL);
                AddEdgeChars(textBlock[i], 1);
            }
            else
            {
                AddEdgeChars(textBlock[i], 1);
                if (i == MID_HEIGHT)
                    AddOutsideLine(textBlock[i], MARKED_DIGIT, 0, LAST_COL_TO_MARKED_ONE);
                else
                    AddOutsideLine(textBlock[i], {}, LAST_COL);
            }
        }

        return textBlock;
    }
};
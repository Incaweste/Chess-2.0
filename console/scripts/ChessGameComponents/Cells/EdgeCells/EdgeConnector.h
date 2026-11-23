#pragma once

#include "BaseEdgeCell.h"
#include "CellsConfiguration.h"
#include "Utilits.h"

class EdgeConnector : public BaseEdgeCell<CellsConfiguration::SPACE_BETWEEN_CELLS, CellsConfiguration::HORIZONTAL_EDGE_HEIGHT>
{
public:
    enum class Type{
        TOP,
        BOTTOM
    };
private:
    const Type CONNECTOR_TYPE;
    const std::size_t FILLED_LINE;
public:
    constexpr EdgeConnector(wchar_t edgeChar, const RGB* cellColor, Type connectorType):
        BaseEdgeCell{edgeChar, cellColor}, CONNECTOR_TYPE{connectorType}, FILLED_LINE{CONNECTOR_TYPE == Type::TOP ? HEIGHT - 1 : 0}
    {
    }

    constexpr EdgeConnector(wchar_t edgeChar, Type connectorType) : EdgeConnector{edgeChar, nullptr, connectorType}
    {
    }

    TextBlock BuildTextBlock(const TextBlock::RGB* outsideTextColor, const TextBlock::RGB* outsideBGColor) const override
    {
        TextBlock textBlock{HEIGHT, WIDTH, outsideTextColor, outsideBGColor, true};

        for (std::size_t i = 0; i < HEIGHT; ++i)
        {
            if (i == FILLED_LINE)
                AddEdgeChars(textBlock[i], WIDTH);
            else
                AddOutsideLine(textBlock[i], {}, WIDTH);
        }

        return textBlock;
    }
};
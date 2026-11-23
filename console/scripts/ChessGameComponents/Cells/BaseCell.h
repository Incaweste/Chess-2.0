#pragma once

#include <functional>
#include <iostream>

#include "Console.h"
#include "ITextBlockBuilder.h"

template<std::size_t width, std::size_t height>
requires(width >= 1 && height >= 1)
class BaseCell : public ITextBlockBuilder
{
protected:
    using RGB = TextBlock::RGB;
    using Color = TextBlock::Color;
    using Line = TextBlock::Line;
public:
    static constexpr std::size_t WIDTH = width;
    static constexpr std::size_t HEIGHT = height;

protected:
    static constexpr const RGB* SELECTED_CELL_COLOR = &Color::YELLOW;
    const RGB* _cellColor;

private:
    const RGB* _unselectedCellColor;

public:
    constexpr explicit BaseCell(const RGB* cellColor) noexcept : _unselectedCellColor{cellColor} 
    {
        SetSelection(false);
    }

    constexpr BaseCell() noexcept : BaseCell{nullptr}
    {
    }
    
    constexpr virtual ~BaseCell() noexcept = default;

    constexpr void SetCellColor(const RGB* cellColor) noexcept
    {
        _unselectedCellColor = cellColor;
    }

    constexpr virtual void SetSelection(bool isSelected)
    {
        _cellColor = isSelected ? SELECTED_CELL_COLOR : _unselectedCellColor;
    }
};
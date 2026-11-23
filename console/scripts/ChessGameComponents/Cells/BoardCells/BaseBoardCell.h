#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "BaseCell.h"
#include "Blinkable.h"
#include "CellsConfiguration.h"
#include "ChessPiece.h"
#include "Console.h"

class BaseBoardCell : 
    public BaseCell<CellsConfiguration::BASE_WIDTH, CellsConfiguration::BASE_HEIGHT>, public Blinkable
{
private:
    struct CellboardParts final
    {
        static inline constexpr wchar_t HORIZONTAL_BORDER = L'\u2500';
        static inline constexpr wchar_t VERTICAL_BORDER = L'\u2502';
        static inline constexpr wchar_t TOP_LEFT_CORNER = L'\u250C';
        static inline constexpr wchar_t TOP_RIGHT_CORNER = L'\u2510';
        static inline constexpr wchar_t BOTTOM_LEFT_CORNER = L'\u2514';
        static inline constexpr wchar_t BOTTOM_RIGHT_CORNER = L'\u2518';

        CellboardParts() = delete;
    };

private:

    static inline constexpr std::size_t LAST_LINE = HEIGHT - 1;
    static inline constexpr std::size_t HORIZONTAL_WIDTH = WIDTH - 2;
    static inline constexpr wchar_t CHARACTER_MARK = L'*';
    bool _isSelected = false;
    bool _isMarked = false;
    
    std::weak_ptr<ChessPiece> _piece;

public:
    BaseBoardCell() = default;
    constexpr explicit BaseBoardCell(const RGB* cellColor) : BaseCell{cellColor}
    {
    }
    inline BaseBoardCell(const RGB* cellColor, std::weak_ptr<ChessPiece> piece);
    inline std::shared_ptr<ChessPiece> GetChessPiece() const noexcept;
    void SetSelection(bool isSelected) override;
    void SetMark(bool isMakred) noexcept;
    inline void SetPieceOnCell(std::weak_ptr<ChessPiece> piece) noexcept;
    inline void RemovePieceFromCell() noexcept;

    TextBlock BuildTextBlock(const TextBlock::RGB* outsideTextColor, const TextBlock::RGB* outsideBGColor) const override;

    void Update() override;
};

#include "BaseBoard.inl"
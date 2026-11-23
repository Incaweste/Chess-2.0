#pragma once

#include <iostream>
#include <memory>
#include <ranges>
#include <vector>

#include "AllEdgeCells.h"
#include "BaseBoardCell.h"
#include "CellsConfiguration.h"
#include "ChessPiece.h"
#include "Console.h"
#include "ITextBlockManager.h"

#include "Utilits.h"
#include "Vector2.h"

class BaseChessboard : public ITextBlockManager
{
protected:
    using Corners = std::array<CornerEdgeCell, 4>;

private:
    using RGB = TextBlock::RGB;
    using Color = TextBlock::Color;
    using Line = TextBlock::Line;

    struct ChessboardParts final
    {
        static inline constexpr wchar_t TOP_BORDER = L'\u2580';  
        static inline constexpr wchar_t BOTTOM_BORDER = L'\u2584';  
        static inline constexpr wchar_t RIGHT_BORDER = L'\u2590';  
        static inline constexpr wchar_t LEFT_BORDER = L'\u258C';  
        static inline constexpr wchar_t TOP_LEFT_CORNER = L'\u259B';  
        static inline constexpr wchar_t TOP_RIGHT_CORNER = L'\u259C';  
        static inline constexpr wchar_t BOTTOM_LEFT_CORNER = L'\u2599';  
        static inline constexpr wchar_t BOTTOM_RIGHT_CORNER = L'\u259F';

        ChessboardParts() = delete;
    };

    struct ChessboardEdges final
    {
        std::array<CornerEdgeCell, 4> corners;
        std::vector<HorizontalEdgeCell> topHorizontalEdge;
        std::vector<HorizontalEdgeCell> bottomHorizontalEdge;
        std::vector<VerticalEdgeCell> leftVerticalEdge;
        std::vector<VerticalEdgeCell> rightVerticalEdge;
        std::vector<EdgeConnector> topEdgeConnectors;
        std::vector<EdgeConnector> bottomEdgeConnectors;
    };

public:
    const std::size_t CHESSBOARD_SIZE;

private:
    const std::size_t CHESSBOARD_SQUARE;
    const Vector2 CHESSBOARD_SIZE_IN_CHARS;
    const std::size_t BOTTOM_EDGE_ROW_INDEX;
    const std::size_t LAST_INDEX_IN_EDGE;
    const RGB* _chessboardTextColor = &Color::WHITE;
    const RGB* _chessboardBGColor = &Color::GRAY;

	std::vector<BaseBoardCell> _cells;
    ChessboardEdges _edges;
    bool _isInverted = false;

    int _selectedCellIndex = -1;
    int _selectedMarkedCellIndex = -1;

    std::vector<Vector2> _positionsOfMarkedCells{};

public:
	constexpr explicit BaseChessboard(std::size_t chessboardSize);
    constexpr BaseChessboard(std::size_t chessboardSize, Corners corners);
    virtual ~BaseChessboard() = default;

    constexpr std::size_t GetChessboardSize() const noexcept;
    constexpr Vector2 GetSizeInChars() const noexcept override;
    constexpr void SetIsInverted(bool isInverted) noexcept;
    inline void SetPieceOnCell(const std::shared_ptr<ChessPiece>& chessPiece, Vector2 position, bool isPlayerMove) noexcept;

    void SetSelectedCell(Vector2 position);
    void SetNextMarkedCell(Utilits::DeltaMove direction);

    [[nodiscard]] 
    bool CalculateAllowedMoves();
    void ClearAllowedMoves();

    bool ConfirmBothSelectedCells();
 
    TextBlock BuildTextBlock(const TextBlock::RGB* outsideTextColor, const TextBlock::RGB* outsideBGColor) const override;
private:
	constexpr void BuildChessboard();

    constexpr void SetEdgesSelection(Vector2 intersection, bool isSelected) noexcept;
    constexpr void SetEdgesSelection(std::size_t intersectionIndex, bool isSelected) noexcept;

    constexpr Vector2 CalculateCellPosition(std::size_t index) const noexcept;
    constexpr std::size_t CalculateCellIndex(Vector2 cellPosition) const noexcept; 

    void SetCellSelection(std::size_t cellIndex, bool isSelected);
    void SetMarkAlongEntireVectorOfMarkedCells(bool isMarked);

    void SortPositionsOfMarkedCells();

    TextBlock BuildHorizontalEdge(bool isTopEdge) const;
};

#include "BaseChessboard.inl"
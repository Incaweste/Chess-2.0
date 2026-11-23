#pragma once

constexpr BaseChessboard::BaseChessboard(std::size_t chessboardSize) : BaseChessboard{chessboardSize, Corners{{
	{ChessboardParts::TOP_LEFT_CORNER, CornerEdgeCell::Type::TOP_LEFT},
	{ChessboardParts::TOP_RIGHT_CORNER, CornerEdgeCell::Type::TOP_RIGHT},
	{ChessboardParts::BOTTOM_LEFT_CORNER, CornerEdgeCell::Type::BOTTOM_LEFT},
	{ChessboardParts::BOTTOM_RIGHT_CORNER, CornerEdgeCell::Type::BOTTOM_RIGHT}
	}}}
{
}

constexpr BaseChessboard::BaseChessboard(std::size_t chessboardSize, Corners corners) : 
	CHESSBOARD_SIZE{chessboardSize}, 
	CHESSBOARD_SQUARE{CHESSBOARD_SIZE * CHESSBOARD_SIZE},
	CHESSBOARD_SIZE_IN_CHARS{
		static_cast<int>(2 * CellsConfiguration::HORIZONTAL_EDGE_HEIGHT + CHESSBOARD_SIZE * CellsConfiguration::BASE_HEIGHT),
		static_cast<int>(2 * CellsConfiguration::VERTICAL_EDGE_WIDTH + 
			CHESSBOARD_SIZE * CellsConfiguration::BASE_WIDTH + 
			(CHESSBOARD_SIZE + 1) * CellsConfiguration::SPACE_BETWEEN_CELLS)
	}, 
	BOTTOM_EDGE_ROW_INDEX{CellsConfiguration::HORIZONTAL_EDGE_HEIGHT + CHESSBOARD_SIZE * CellsConfiguration::BASE_HEIGHT},
    LAST_INDEX_IN_EDGE{CHESSBOARD_SIZE - 1},
	_edges{.corners = std::move(corners)}
{
	BuildChessboard();
}

constexpr std::size_t BaseChessboard::GetChessboardSize() const noexcept
{
	return CHESSBOARD_SIZE;
}

constexpr Vector2 BaseChessboard::GetSizeInChars() const noexcept
{
	return CHESSBOARD_SIZE_IN_CHARS;
}

constexpr void BaseChessboard::SetIsInverted(bool isInverted) noexcept
{
    _isInverted = isInverted;
}

inline void BaseChessboard::SetPieceOnCell(const std::shared_ptr<ChessPiece>& chessPiece, Vector2 position, bool isPlayerMove) noexcept
{
	if (chessPiece != nullptr && position.row < CHESSBOARD_SIZE && position.col < CHESSBOARD_SIZE)
	{
		chessPiece->SetPosition(position, isPlayerMove);
		_cells[position.row * CHESSBOARD_SIZE + position.col].SetPieceOnCell(chessPiece);
	}
}

constexpr void BaseChessboard::BuildChessboard()
{
	_edges.topHorizontalEdge.reserve(CHESSBOARD_SIZE);
	_edges.bottomHorizontalEdge.reserve(CHESSBOARD_SIZE);
	_edges.leftVerticalEdge.reserve(CHESSBOARD_SIZE);
	_edges.rightVerticalEdge.reserve(CHESSBOARD_SIZE);

	_cells.resize(CHESSBOARD_SIZE * CHESSBOARD_SIZE);

	const std::size_t CHESSBOARD_SIZE_ONE_LARGER = CHESSBOARD_SIZE + 1;
	_edges.topEdgeConnectors.reserve(CHESSBOARD_SIZE_ONE_LARGER);
	_edges.bottomEdgeConnectors.reserve(CHESSBOARD_SIZE_ONE_LARGER);

	wchar_t firstMarkedLetter = 'A', currentMarkedLetter;
	for (std::size_t i = 0, rowNumber; i < CHESSBOARD_SIZE; ++i)
	{
		rowNumber = CHESSBOARD_SIZE - i;
		currentMarkedLetter = firstMarkedLetter + i;

		_edges.topHorizontalEdge.emplace_back(ChessboardParts::TOP_BORDER, currentMarkedLetter, HorizontalEdgeCell::Type::TOP);
		_edges.bottomHorizontalEdge.emplace_back(ChessboardParts::BOTTOM_BORDER, currentMarkedLetter, HorizontalEdgeCell::Type::BOTTOM);
		_edges.leftVerticalEdge.emplace_back(ChessboardParts::LEFT_BORDER, rowNumber, VerticalEdgeCell::Type::LEFT);
		_edges.rightVerticalEdge.emplace_back(ChessboardParts::RIGHT_BORDER, rowNumber, VerticalEdgeCell::Type::RIGHT);
	}

	for (std::size_t i = 0; i < CHESSBOARD_SIZE_ONE_LARGER; ++i)
	{
		_edges.topEdgeConnectors.emplace_back(ChessboardParts::TOP_BORDER, EdgeConnector::Type::TOP);
		_edges.bottomEdgeConnectors.emplace_back(ChessboardParts::BOTTOM_BORDER, EdgeConnector::Type::BOTTOM);
	}
}


constexpr void BaseChessboard::SetEdgesSelection(Vector2 intersection, bool isSelected) noexcept
{
	_edges.topHorizontalEdge[intersection.col].SetSelection(isSelected);
	_edges.bottomHorizontalEdge[intersection.col].SetSelection(isSelected);
	_edges.leftVerticalEdge[intersection.row].SetSelection(isSelected);
	_edges.rightVerticalEdge[intersection.row].SetSelection(isSelected);
}

constexpr void BaseChessboard::SetEdgesSelection(std::size_t intersectionIndex, bool isSelected) noexcept
{
	SetEdgesSelection(CalculateCellPosition(intersectionIndex), isSelected);
}

constexpr Vector2 BaseChessboard::CalculateCellPosition(std::size_t cellIndex) const noexcept
{
	return Vector2{static_cast<int>(cellIndex / CHESSBOARD_SIZE), static_cast<int>(cellIndex % CHESSBOARD_SIZE)};
}

constexpr std::size_t BaseChessboard::CalculateCellIndex(Vector2 cellPosition) const noexcept
{
	return cellPosition.row * CHESSBOARD_SIZE + cellPosition.col;
}
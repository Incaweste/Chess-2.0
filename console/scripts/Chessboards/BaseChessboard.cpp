#include "BaseChessboard.h"

BaseChessboard::BaseChessboard(std::size_t chessboardSize): BaseChessboard{chessboardSize, Corners{{
	{ChessboardParts::TOP_LEFT_CORNER, CornerEdgeCell::Type::TOP_LEFT},
	{ChessboardParts::TOP_RIGHT_CORNER, CornerEdgeCell::Type::TOP_RIGHT},
	{ChessboardParts::BOTTOM_LEFT_CORNER, CornerEdgeCell::Type::BOTTOM_LEFT},
	{ChessboardParts::BOTTOM_RIGHT_CORNER, CornerEdgeCell::Type::BOTTOM_RIGHT}
	}}}
{
}

BaseChessboard::BaseChessboard(std::size_t chessboardSize, Corners corners) :
	CHESSBOARD_SIZE{chessboardSize}, 
	CHESSBOARD_SQUARE{CHESSBOARD_SIZE * CHESSBOARD_SIZE},
	CHESSBOARD_SIZE_IN_CHARS{
		static_cast<int>(2 * CellsConfiguration::HORIZONTAL_EDGE_HEIGHT + CHESSBOARD_SIZE * CellsConfiguration::BASE_HEIGHT),
		static_cast<int>(2 * CellsConfiguration::VERTICAL_EDGE_WIDTH + 
			CHESSBOARD_SIZE * CellsConfiguration::BASE_WIDTH + 
			(CHESSBOARD_SIZE + 1) * CellsConfiguration::SPACE_BETWEEN_CELLS)
	}, 
	_edges{.corners = std::move(corners)}
{
	BuildChessboard();
}

std::size_t BaseChessboard::GetChessboardSize() const noexcept
{
	return CHESSBOARD_SIZE;
}

void BaseChessboard::SetPieceOnCell(std::weak_ptr<ChessPiece> chessPiece, Vector2 position) noexcept
{
	auto realChessPiece = chessPiece.lock();
	if (realChessPiece != nullptr && position.row < CHESSBOARD_SIZE && position.col < CHESSBOARD_SIZE)
	{
		realChessPiece->SetPosition(position);
		_cells[position.row * CHESSBOARD_SIZE + position.col].SetPieceOnCell(chessPiece);
	}
}

void BaseChessboard::SetSelectedCell(Vector2 position)
{
	SetCellSelection(_selectedCellIndex, false);
	if (position.row < CHESSBOARD_SIZE && position.col < CHESSBOARD_SIZE)
	{
		std::size_t index = CalculateCellIndex(position);
		SetCellSelection(index, true);
		_selectedCellIndex = index;
	}
	else
		_selectedCellIndex = -1;
}

void BaseChessboard::SetNextMarkedCell(Utilits::DeltaMove direction)
{
	int nextMarkedIndex = Utilits::FindNextPositionIndex(
		_positionsOfMarkedCells, 
		CalculateCellPosition(_selectedMarkedCellIndex), 
		direction, 
		CHESSBOARD_SIZE);

	int nextGlobalIndex = CalculateCellIndex(_positionsOfMarkedCells[nextMarkedIndex]);

	if (nextGlobalIndex >= 0)
	{
		SetCellSelection(_selectedMarkedCellIndex, false);

		_selectedMarkedCellIndex = nextGlobalIndex;
		SetCellSelection(_selectedMarkedCellIndex, true);
	}
}

Vector2 BaseChessboard::GetSizeInChars() const noexcept
{
	return CHESSBOARD_SIZE_IN_CHARS;
}

bool BaseChessboard::CalculateAllowedMoves()
{
	if (_positionsOfMarkedCells.size() > 0)
		ClearAllowedMoves();

	if (_selectedCellIndex < 0)
		return false;

	std::shared_ptr<ChessPiece> selectedChessPiece = _cells[_selectedCellIndex].GetChessPiece();
	if (selectedChessPiece == nullptr)
		return false;

	std::size_t countOfFullPaths = selectedChessPiece->GetCountOfFullPaths();

	Vector2 anchoredPosition = CalculateCellPosition(_selectedCellIndex);
	std::span<const ChessPiece::MovePosition> _fullPathForMove;
	for (int i = 0; i < countOfFullPaths; ++i)
	{
		_fullPathForMove = selectedChessPiece->GetFullPathForMove(i);
		for (const auto& el : _fullPathForMove)
		{
			Vector2 elPosition = anchoredPosition + el.GetPosition();
			if (!(elPosition.row >= 0 && elPosition.col >= 0 && elPosition.row < CHESSBOARD_SIZE && elPosition.col < CHESSBOARD_SIZE))
				break;

			std::shared_ptr<ChessPiece> potentOppositePiece = _cells[CalculateCellIndex(elPosition)].GetChessPiece();
			
			if (potentOppositePiece != nullptr)
			{
				if (potentOppositePiece->GetIsWhite() != selectedChessPiece->GetIsWhite())
					_positionsOfMarkedCells.push_back(elPosition);
				break;
			}
			else if (el.GetIsMoveForCapturingPieceOnly())
				break;

			_positionsOfMarkedCells.push_back(elPosition);
		}
	}
	if (_positionsOfMarkedCells.size() > 0)
	{
		SortPositionsOfMarkedCells();
		SetMarkAlongEntireVectorOfMarkedCells(true);
		return true;
	}
	else 
		return false;
}

void BaseChessboard::ClearAllowedMoves()
{
	SetMarkAlongEntireVectorOfMarkedCells(false);
	_positionsOfMarkedCells.clear();
}

TextBlock BaseChessboard::BuildTextBlock(const TextBlock::RGB* textColor, const TextBlock::RGB* bgColor) const
{
	TextBlock boardTextBlock{
		CHESSBOARD_SIZE_IN_CHARS.row,
		CHESSBOARD_SIZE_IN_CHARS.col,
		_chessboardTextColor, 
		_chessboardBGColor,
		false
	};

	boardTextBlock.MergeWithTextBlock(BuildHorizontalEdge(true));

	for (std::size_t i = 0; i < CHESSBOARD_SIZE; ++i)
	{
		std::size_t startIndexForSubTextBlock = CellsConfiguration::HORIZONTAL_EDGE_HEIGHT + i * CellsConfiguration::BASE_HEIGHT;
		boardTextBlock.MergeWithTextBlock(
				_edges.leftVerticalEdge[i].BuildTextBlock(_chessboardTextColor, _chessboardBGColor),
				startIndexForSubTextBlock
			);
		
		std::size_t rowOffset = i * CHESSBOARD_SIZE;
		for (std::size_t j = 0; j < CHESSBOARD_SIZE; ++j)
			{
				boardTextBlock.AddCharsForSeveralLines(startIndexForSubTextBlock, CellsConfiguration::BASE_HEIGHT);
				boardTextBlock.MergeWithTextBlock(
					_cells[rowOffset + j].BuildTextBlock(_chessboardTextColor, _chessboardBGColor),
					startIndexForSubTextBlock
				);
			}

		boardTextBlock.AddCharsForSeveralLines(startIndexForSubTextBlock, CellsConfiguration::BASE_HEIGHT);
		boardTextBlock.MergeWithTextBlock(
				_edges.rightVerticalEdge[i].BuildTextBlock(_chessboardTextColor, _chessboardBGColor),
				startIndexForSubTextBlock
			);
	}
	
	boardTextBlock.MergeWithTextBlock(
		BuildHorizontalEdge(false), 
	CellsConfiguration::HORIZONTAL_EDGE_HEIGHT + CHESSBOARD_SIZE * CellsConfiguration::BASE_HEIGHT
	);

	return boardTextBlock;
}

void BaseChessboard::BuildChessboard()
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

void BaseChessboard::SetCellSelection(std::size_t cellIndex, bool isSelected)
{
	if (cellIndex < CHESSBOARD_SQUARE)
	{
		Vector2 position = CalculateCellPosition(cellIndex);
		_cells[cellIndex].SetSelection(isSelected);
		SetEdgesSelection(position, isSelected);
	}
}

void BaseChessboard::SetEdgesSelection(Vector2 intersection, bool isSelected)
{
	_edges.topHorizontalEdge[intersection.col].SetSelection(isSelected);
	_edges.bottomHorizontalEdge[intersection.col].SetSelection(isSelected);
	_edges.leftVerticalEdge[intersection.row].SetSelection(isSelected);
	_edges.rightVerticalEdge[intersection.row].SetSelection(isSelected);
}

void BaseChessboard::SetEdgesSelection(std::size_t intersectionIndex, bool isSelected)
{
	SetEdgesSelection(CalculateCellPosition(intersectionIndex), isSelected);
}

void BaseChessboard::SetMarkAlongEntireVectorOfMarkedCells(bool isMarked)
{

	for (const Vector2& el : _positionsOfMarkedCells)
		_cells[CalculateCellIndex(el)].SetMark(isMarked);

	int nearestMarkedIndex = Utilits::FindNextPositionIndex(
		_positionsOfMarkedCells, 
		CalculateCellPosition(_selectedCellIndex), 
		Utilits::DeltaMove::UP, 
		CHESSBOARD_SIZE);
	int nearestGlobalIndex = CalculateCellIndex(_positionsOfMarkedCells[nearestMarkedIndex]);
		
	if (isMarked && nearestGlobalIndex >= 0)
	{
		SetEdgesSelection(_selectedCellIndex, false);

		_selectedMarkedCellIndex = nearestGlobalIndex;
		SetCellSelection(_selectedMarkedCellIndex, true);
	}
	else if (_selectedMarkedCellIndex >= 0)
	{
		SetCellSelection(_selectedMarkedCellIndex, false);
		_selectedMarkedCellIndex = -1;
		
		SetEdgesSelection(_selectedCellIndex, true);
	}
}

inline Vector2 BaseChessboard::CalculateCellPosition(std::size_t cellIndex) const noexcept
{
	return Vector2{static_cast<int>(cellIndex / CHESSBOARD_SIZE), static_cast<int>(cellIndex % CHESSBOARD_SIZE)};
}

inline std::size_t BaseChessboard::CalculateCellIndex(Vector2 cellPosition) const noexcept
{
	return cellPosition.row * CHESSBOARD_SIZE + cellPosition.col;
}

void BaseChessboard::SortPositionsOfMarkedCells()
{
	std::ranges::sort(_positionsOfMarkedCells, {}, [](const Vector2& v){
		return std::tie(v.row, v.col);
	});
}

TextBlock BaseChessboard::BuildHorizontalEdge(bool isTopEdge) const
{
	const CornerEdgeCell* leftCorner;
	const CornerEdgeCell* rightCorner;
	const std::vector<HorizontalEdgeCell>* horizontalEdge;
	const std::vector<EdgeConnector>* connectors;

	if(isTopEdge)
	{
		leftCorner = &_edges.corners[0];
		rightCorner = &_edges.corners[1];
		horizontalEdge = &_edges.topHorizontalEdge;
		connectors = &_edges.topEdgeConnectors;
	}
	else
	{
		leftCorner = &_edges.corners[2];
		rightCorner = &_edges.corners[3];
		horizontalEdge = &_edges.bottomHorizontalEdge;
		connectors = &_edges.bottomEdgeConnectors;
	}

	TextBlock textBlock{
		CellsConfiguration::HORIZONTAL_EDGE_HEIGHT, 
		2 * CellsConfiguration::VERTICAL_EDGE_WIDTH + CHESSBOARD_SIZE * CellsConfiguration::BASE_WIDTH,  
		_chessboardTextColor, 
		_chessboardBGColor, 
		true};

	textBlock.MergeWithTextBlock(leftCorner->BuildTextBlock(_chessboardTextColor, _chessboardBGColor));
	for (std::size_t j = 0; j < CHESSBOARD_SIZE; ++j)
	{
		textBlock.MergeWithTextBlock((*connectors)[j].BuildTextBlock(_chessboardTextColor, _chessboardBGColor));
		textBlock.MergeWithTextBlock((*horizontalEdge)[j].BuildTextBlock(_chessboardTextColor, _chessboardBGColor));
	}
	textBlock.MergeWithTextBlock((*connectors)[CHESSBOARD_SIZE].BuildTextBlock(_chessboardTextColor, _chessboardBGColor));
	textBlock.MergeWithTextBlock(rightCorner->BuildTextBlock(_chessboardTextColor, _chessboardBGColor));

	return textBlock;
}
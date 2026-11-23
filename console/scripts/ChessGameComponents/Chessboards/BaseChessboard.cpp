#include "BaseChessboard.h"

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
	if(_selectedMarkedCellIndex < 0)
		return;

	int nextMarkedIndex = Utilits::FindNextPositionIndex<Vector2>(
		_positionsOfMarkedCells, 
		CalculateCellPosition(_selectedMarkedCellIndex), 
		CHESSBOARD_SIZE,
		direction,
		_isInverted
	);

	if (nextMarkedIndex >= 0)
	{
		std::size_t nextGlobalIndex = CalculateCellIndex(_positionsOfMarkedCells[nextMarkedIndex]);
		SetCellSelection(_selectedMarkedCellIndex, false);

		_selectedMarkedCellIndex = nextGlobalIndex;
		SetCellSelection(_selectedMarkedCellIndex, true);
	}
}

#define CONTINUE_OR_BREAK_IF(flagsForContinue)		\
	if(el.HasModifiers((flagsForContinue)))			\
		continue;									\
	else											\
		break

bool BaseChessboard::CalculateAllowedMoves()
{
	if (_positionsOfMarkedCells.size() > 0)
		ClearAllowedMoves();

	if (_selectedCellIndex < 0)
		return false;

	std::shared_ptr<ChessPiece> selectedChessPiece = _cells[_selectedCellIndex].GetChessPiece();
	if (selectedChessPiece == nullptr)
		return false;

	bool hadFirstMove = selectedChessPiece->GetHadFirstMove();
	bool isWhite = selectedChessPiece->GetIsWhite();

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
				CONTINUE_OR_BREAK_IF(ChessPiece::MoveModifiers::CONTINUE_DESPITE_BORDERS);
			
			if (el.HasModifiers(ChessPiece::MoveModifiers::CAN_BE_FIRST_ONLY) && hadFirstMove)
				CONTINUE_OR_BREAK_IF(ChessPiece::MoveModifiers::CONTINUE_DESPITE_FLAGS);
			std::shared_ptr<ChessPiece> potentOppositePiece = _cells[CalculateCellIndex(elPosition)].GetChessPiece();

			if (potentOppositePiece != nullptr)
			{
				if (
					el.HasModifiers(ChessPiece::MoveModifiers::MOVE_WITH_CAPTURING) && 
					potentOppositePiece->GetIsWhite() != isWhite
				)
					_positionsOfMarkedCells.push_back(elPosition);

				CONTINUE_OR_BREAK_IF(ChessPiece::MoveModifiers::CONTINUE_DESPITE_PIECES);
			}
			else if (el.HasModifiers(ChessPiece::MoveModifiers::MOVE_TO_EMPTY_CELL))
				_positionsOfMarkedCells.push_back(elPosition);
			else
			{
				CONTINUE_OR_BREAK_IF(ChessPiece::MoveModifiers::CONTINUE_DESPITE_FLAGS);
			}
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

#undef CONTINUE_OR_BREAK_IF

void BaseChessboard::ClearAllowedMoves()
{
	SetMarkAlongEntireVectorOfMarkedCells(false);
	_positionsOfMarkedCells.clear();
}

bool BaseChessboard::ConfirmBothSelectedCells()
{
	if (_selectedCellIndex < 0 || _selectedMarkedCellIndex < 0)
		return false;

	
	auto movingPiece = _cells[_selectedCellIndex].GetChessPiece();
	if (movingPiece != nullptr)
	{
		auto erasingPiece = _cells[_selectedMarkedCellIndex].GetChessPiece();
		if (erasingPiece == nullptr || erasingPiece->GetIsWhite() != movingPiece->GetIsWhite())
		{
			_cells[_selectedCellIndex].RemovePieceFromCell();
			if (erasingPiece != nullptr)
				erasingPiece->SetErasureMark();
			SetPieceOnCell(movingPiece, CalculateCellPosition(_selectedMarkedCellIndex), true);

			ClearAllowedMoves();
			SetSelectedCell(movingPiece->GetPosition());
			return true;
		}
	}

	return false;
}

TextBlock BaseChessboard::BuildTextBlock(const TextBlock::RGB* outsideTextColor, const TextBlock::RGB* outsideBGColor) const
{
	TextBlock boardTextBlock{
		static_cast<std::size_t>(CHESSBOARD_SIZE_IN_CHARS.row),
		static_cast<std::size_t>(CHESSBOARD_SIZE_IN_CHARS.col),
		_chessboardTextColor, 
		_chessboardBGColor,
		false
	};

	boardTextBlock.MergeWithTextBlock(BuildHorizontalEdge(true));

	std::size_t cellsCount =  _cells.size();
	auto cellsView = std::views::iota(0ull, cellsCount) | 
		std::views::transform([this, lastCellsIndex = cellsCount - 1](std::size_t i) -> const BaseBoardCell& {
		return  _cells[_isInverted ? lastCellsIndex - i : i];
	});

	for (std::size_t edgeIndex, i = 0; i < CHESSBOARD_SIZE; ++i)
	{
		edgeIndex = _isInverted ? LAST_INDEX_IN_EDGE - i : i;
		std::size_t startIndexForSubTextBlock = CellsConfiguration::HORIZONTAL_EDGE_HEIGHT + i * CellsConfiguration::BASE_HEIGHT;
		boardTextBlock.MergeWithTextBlock(
				_edges.leftVerticalEdge[edgeIndex].BuildTextBlock(_chessboardTextColor, _chessboardBGColor),
				startIndexForSubTextBlock
			);
		
		std::size_t rowOffset = i * CHESSBOARD_SIZE;
		for (std::size_t j = 0; j < CHESSBOARD_SIZE; ++j)
			{
				boardTextBlock.AddCharsForSeveralLines(startIndexForSubTextBlock, CellsConfiguration::BASE_HEIGHT);
				boardTextBlock.MergeWithTextBlock(
					cellsView[rowOffset + j].BuildTextBlock(_chessboardTextColor, _chessboardBGColor),
					startIndexForSubTextBlock
				);
			}

		boardTextBlock.AddCharsForSeveralLines(startIndexForSubTextBlock, CellsConfiguration::BASE_HEIGHT);
		boardTextBlock.MergeWithTextBlock(
				_edges.rightVerticalEdge[edgeIndex].BuildTextBlock(_chessboardTextColor, _chessboardBGColor),
				startIndexForSubTextBlock
			);
	}
	
	boardTextBlock.MergeWithTextBlock(BuildHorizontalEdge(false), BOTTOM_EDGE_ROW_INDEX);

	if (outsideTextColor != nullptr)
		boardTextBlock.SetActiveColorForAllLines(TextBlock::ColorTarget::TEXT, outsideTextColor);

	if (outsideBGColor != nullptr)
		boardTextBlock.SetActiveColorForAllLines(TextBlock::ColorTarget::BACKGROUND, outsideBGColor);

	return boardTextBlock;
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

void BaseChessboard::SetMarkAlongEntireVectorOfMarkedCells(bool isMarked)
{
	for (const Vector2& el : _positionsOfMarkedCells)
		_cells[CalculateCellIndex(el)].SetMark(isMarked);

	if (!isMarked)
	{
		if (_selectedMarkedCellIndex >= 0)
		{
			SetCellSelection(_selectedMarkedCellIndex, false);
			_selectedMarkedCellIndex = -1;
			SetEdgesSelection(_selectedCellIndex, true);
		}
		return;
	}

	int nearestMarkedIndex = Utilits::FindNextPositionIndex<Vector2>(
		_positionsOfMarkedCells, 
		CalculateCellPosition(_selectedCellIndex), 
		CHESSBOARD_SIZE,
		Utilits::DeltaMove::UP, 
		false
	);

		
	if (nearestMarkedIndex >= 0)
	{
		SetEdgesSelection(_selectedCellIndex, false);
		_selectedMarkedCellIndex = CalculateCellIndex(_positionsOfMarkedCells[nearestMarkedIndex]);
		SetCellSelection(_selectedMarkedCellIndex, true);
	}
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

	for (std::size_t edgeIndex, connectorIndex, i = 0; i < CHESSBOARD_SIZE; ++i)
	{
		if (_isInverted)
		{
			connectorIndex = CHESSBOARD_SIZE - i;
			edgeIndex = connectorIndex - 1;
		}
		else
			connectorIndex = edgeIndex = i;

		textBlock.MergeWithTextBlock((*connectors)[connectorIndex].BuildTextBlock(_chessboardTextColor, _chessboardBGColor));
		textBlock.MergeWithTextBlock((*horizontalEdge)[edgeIndex].BuildTextBlock(_chessboardTextColor, _chessboardBGColor));
	}

	textBlock.MergeWithTextBlock((*connectors)[_isInverted ? 0 : CHESSBOARD_SIZE].BuildTextBlock(_chessboardTextColor, _chessboardBGColor));
	
	textBlock.MergeWithTextBlock(rightCorner->BuildTextBlock(_chessboardTextColor, _chessboardBGColor));

	return textBlock;
}
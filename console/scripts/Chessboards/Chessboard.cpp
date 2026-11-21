#include "Chessboard.h"

Chessboard::ChessboardParts::~ChessboardParts() = default;

Chessboard::Chessboard(int boardSize, bool isActive): _chessBoardSize{boardSize}, _isActive{isActive}
{
	BuildChessboard();

	_totalWidth = _chessBoardSize * (Cell::WIDTH+1) + 1;
	_totalHeight = _chessBoardSize * Cell::HEIGHT;
}

void Chessboard::Update()
{
	if (_isActive)
	{
		PrintChessboard();
	}
}

int Chessboard::GetWidth() const
{
	return _totalWidth;
}

int Chessboard::GetHeight() const
{
	return _totalHeight;
}

void Chessboard::BuildChessboard()
{
	_cells.resize(_chessBoardSize*_chessBoardSize);

	for (int i = 0; i < _chessBoardSize; ++i)
	{
		const int rowOffset = i * _chessBoardSize;
	    for (int j = 0; j < _chessBoardSize; ++j)
	    {
	        _cells[rowOffset+j] = std::make_unique<Cell>(&Console::Color::WHITE);
	    }
	}
}

void Chessboard::PrintChessboard() const
{
	Console::SetTextColor(&Color::WHITE);
	Console::SetBGColor(&Color::GRAY);

	std::wcout << ChessboardParts::TOP_LEFT_CORNER;
	std::wcout << std::wstring(_totalWidth, ChessboardParts::TOP_BORDER);
	std::wcout << ChessboardParts::TOP_RIGHT_CORNER << std::endl;

	for (std::size_t cellRow = 0; cellRow < _chessBoardSize; ++cellRow)
	{
	    for (std::size_t cellLine = 0; cellLine < Cell::HEIGHT; ++cellLine)
	    {

	        std::wcout << ChessboardParts::LEFT_BORDER << L' ';

			const std::size_t rowOffset = cellRow * _chessBoardSize;
		
	        for (std::size_t j = 0; j < _chessBoardSize; ++j)
	        {
	            std::size_t cellIndex = rowOffset + j;
			
	            _cells[cellIndex]->DrawCell(cellLine);
	        }

			Console::SetTextColor(&Color::WHITE);
	        std::wcout << ChessboardParts::RIGHT_BORDER << std::endl;
	    }
	}
	
	std::wcout << ChessboardParts::BOTTOM_LEFT_CORNER;
	std::wcout << std::wstring(_totalWidth, ChessboardParts::BOTTOM_BORDER);
	std::wcout << ChessboardParts::BOTTOM_RIGHT_CORNER << std::flush;
	Console::ResetConsoleColor();
}
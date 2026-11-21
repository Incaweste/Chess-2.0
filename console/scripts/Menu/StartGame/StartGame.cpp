#include "StartGame.h"

StartGame::StartGame() : InfoWindowBase()
{
    _chessBoard = std::make_unique<Chessboard>(8);

	_totalHeight = _chessBoard->GetHeight();
	_totalWidth = _chessBoard->GetWidth();
}

void StartGame::Update()
{
    if (_isActive)
    {
        PrintContent();
    }
}

void StartGame::PrintContent() const
{
	//DEBUG
    _chessBoard->Update();
}

std::optional<MenuAction> StartGame::HandleMenuSelect()
{
	if (_isActive)
	{
		HandleInput();
		return std::nullopt;
	} 
	else
	{
		Console::RefreshConsole();
		return MenuAction::MainMenu;
	}
}

void StartGame::HandleInput()
{
    if (!_kbhit())
        return;

    int inputCode = _getch();

    if (inputCode == 27)
        _isActive = false;
}


#include "GameManagement.h"

GameManagement::GameManagement(int edgeLength, int maxChessPiecesValue)
{
    _chessboard = std::make_unique<Chessboard>(edgeLength, maxChessPiecesValue);
    std::wcout << L"GameManagement was created" << std::endl;
}

GameManagement::~GameManagement()
{
	std::wcout << L"GameManagement was destroyed" << std::endl;
}

Chessboard& GameManagement::GetChessboard() const
{
    return *_chessboard;
}

void GameManagement::Update()
{
	while (_isGameRunning)
	{
	   ClearConsole();
	   _chessboard->Update();
		std::this_thread::sleep_for(std::chrono::milliseconds(_FRAME_DELAY_MIL_SEC));

        PickUpInput();
	}
    std::wcout << std::endl;
}

void GameManagement::ClearConsole() const
{
	std::wcout << L"\033[2J\033[3J\033[1;1H" << std::flush;
}

void GameManagement::PickUpInput()
{
	if (_kbhit())
	{
		if (_getch() == 27)
			_isGameRunning = false;
	}
}

#include "GameManagement.h"
GameManagement::GameManagement()
{
	//_chessboard = new Chessboard(8);
	_mainMenuWindow = std::make_unique<MainMenuWindow>();
	_frameInfoWindow =
        std::make_unique<FrameForInfoWindow>(*_mainMenuWindow);

	Console::RefreshConsole();
}

GameManagement::~GameManagement()
{
	//delete _chessboard;
}

GameManagement& GameManagement::GetGameManagement()
{
	static GameManagement gameManagement;
	return gameManagement;	
}

void GameManagement::SetGUIConfines(int rowCnt, int colCnt)
{
	_minRowCnt = rowCnt;
	_minColCnt = colCnt + 1;
}

void GameManagement::Update()
{
	bool wasConsoleFit = false;
	while (_isGameRunning)
	{
		Console::ResetCaret();

		bool isConsoleFit =
            Console::IsThisFitInConsole(_minRowCnt, _minColCnt);

		if (isConsoleFit != wasConsoleFit)
		{
			Console::RefreshConsole();
			wasConsoleFit = isConsoleFit;
		}

		if (isConsoleFit)
		{
			//_chessboard->Update();
			_frameInfoWindow->Update();
		}
		else
			std::wcout << L"Not enough space for GUI\033[J" << std::flush;

		std::this_thread::sleep_for(_FRAME_DELAY_MIL_SEC);
		PickUpInput();
	}
}

void GameManagement::PickUpInput()
{
	if (_kbhit())
	{
		int inputCode = _getch();
		if (inputCode == 27)
			_isGameRunning = false;
		else if (inputCode == 0 || inputCode == 224)
		{
			inputCode = _getch();
			if(inputCode == 98)
				Console::RefreshConsole();
		}
	}
}
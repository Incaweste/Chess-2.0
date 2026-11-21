#include "GameManagement.h"

GameManagement::GameManagement()
{
	_mainMenu = std::make_shared<MainMenu>();
	_startGameMenu = std::make_shared<StartGame>();

	_activeWindow = _mainMenu;

	Console::RefreshConsole();
}

GameManagement::~GameManagement() = default;

GameManagement& GameManagement::GetGameManagement()
{
	static GameManagement gameManagement;
	return gameManagement;	
}

void GameManagement::ProcessMenuAction(MenuAction action)
{
	if (action == MenuAction::MainMenu)
	{
		_activeWindow = _mainMenu;
	}
	else if (action == MenuAction::StartGame)
	{
		_activeWindow = _startGameMenu;
	}
	else if (action == MenuAction::Exit)
	{
		_isGameRunning = false;
	}

	if (auto window = _activeWindow.lock())
		window->NowActive();
}

void GameManagement::Update()
{
	bool wasConsoleFit = false;
	while (_isGameRunning)
	{
		Console::ResetCaret();

		bool isConsoleFit = false;
		auto window = _activeWindow.lock();
		
		if (window)
        {
            isConsoleFit = Console::IsThisFitInConsole(
                window->GetRequiredHeight(),
                window->GetRequiredWidth()
            );
        }

		if (isConsoleFit != wasConsoleFit)
		{
			Console::RefreshConsole();
			wasConsoleFit = isConsoleFit;
		}

		if (isConsoleFit && window)
		{
			window->Update();

			if (auto menu = std::dynamic_pointer_cast<IMenuInput>(window))
			{
			    if (auto action = menu->HandleMenuSelect())
			        ProcessMenuAction(*action);
			}
		}
		else
			std::wcout << L"Not enough space for GUI\033[J" << std::flush;

		std::this_thread::sleep_for(_FRAME_DELAY_MIL_SEC);
	}
	Console::RefreshConsole();
}
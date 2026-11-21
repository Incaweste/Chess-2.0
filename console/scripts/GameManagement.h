#pragma once

#include <conio.h>
#include <iostream>
#include <thread>

#include "IUpdatable.h"
#include "Chessboard.h"
#include "AllMenuWindows.h"
#include "Console.h"
#include "MenuAction.h"

class GameManagement : public IUpdatable
{
private:
    static inline const auto _FRAME_DELAY_MIL_SEC = std::chrono::milliseconds(100);
    bool _isGameRunning = true;

    std::shared_ptr<MainMenu> _mainMenu;
    std::shared_ptr<StartGame> _startGameMenu;

    std::weak_ptr<InfoWindowBase> _activeWindow;

public:
    GameManagement(const GameManagement& other) = delete;
    static GameManagement& GetGameManagement();

    void ProcessMenuAction(MenuAction action);

	void Update() override;

private:
    GameManagement();
    ~GameManagement();
};
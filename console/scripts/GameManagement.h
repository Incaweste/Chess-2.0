#pragma once

#include <conio.h>
#include <iostream>
#include <thread>

#include "IUpdatable.h"
#include "Chessboard.h"
#include "AllMenuWindows.h"
#include "Console.h"

class GameManagement : public IUpdatable
{
private:
    static inline const auto _FRAME_DELAY_MIL_SEC = std::chrono::milliseconds(100);
    bool _isGameRunning = true;
    static inline int _minRowCnt = 26;
    static inline int _minColCnt = 52;

    //DEBUG
    std::unique_ptr<MainMenuContent> _mainMenuContent;
    std::unique_ptr<MainMenuFrame> _mainMenuFrame;
public:
    GameManagement(const GameManagement& other) = delete;
    static GameManagement& GetGameManagement();

    static void SetGUIConfines(int rowCnt, int colCnt);
	void Update() override;

private:
    GameManagement();
    ~GameManagement();
    
    void PickUpInput();
};
#pragma once
#include <conio.h>
#include <iostream>
#include <memory>
#include <thread>
#include "Chessboard.h"

class GameManagement
{
private:
    static constexpr int _FRAME_DELAY_MIL_SEC = 1000;

    std::unique_ptr<Chessboard> _chessboard;
    bool _isGameRunning = true;
public:
    GameManagement(int edgeLength, int chessPiecesValue);
    ~GameManagement();
    void Update();
    Chessboard& GetChessboard() const;
private:
    void ClearConsole() const;
    void PickUpInput();
};

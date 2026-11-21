#pragma once

#include "InfoWindowBase.h"
#include "IMenuInput.h"
#include "Chessboard.h"

class StartGame : public InfoWindowBase, public IMenuInput
{
private:
    std::unique_ptr<Chessboard> _chessBoard;

public:
    StartGame();

    void Update() override;

    void PrintContent() const override;
    std::optional<MenuAction> HandleMenuSelect() override;

    void HandleInput();
};
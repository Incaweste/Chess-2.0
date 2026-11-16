#pragma once

#include <iostream>
#include <windows.h>
#undef RGB

#include "BaseChessboard.h"
#include "Blinkable.h"
#include "Console.h"
#include "IUpdatable.h"
#include "Player.h"
#include "TextBlock.h"

class GameManagement : public IUpdatable
{
public:
    enum class GameState
    {
        OFF,
        MAIN_MENU,
        PIECE_SELECTION,
        PATH_SELECTION
    };
private:
    GameState _currentGameState = GameState::PIECE_SELECTION;

    std::shared_ptr<BaseChessboard> _chessboard;
    //std::vector<ITextBlockManager> _activeBlocks; ???

    std::unique_ptr<Player> _activePlayer;
    std::unique_ptr<Player> _inactivePlayer;
public:
    static GameManagement& GetGameManagement() noexcept;

    GameManagement(const GameManagement& other) = delete;
    GameManagement(GameManagement&& other) = delete;
    GameManagement& operator=(const GameManagement& other) = delete;
    GameManagement& operator=(GameManagement&& other) = delete;

    void StartGame();

    Vector2 GetSizeOfActiveBlocks() const noexcept;
    std::vector<TextBlock> GetActiveBlocks() const;
	void Update() override;

private:
    GameManagement() noexcept = default;
    ~GameManagement() noexcept = default;
    
    void ProcessKeyboardInput(std::span<const KEY_EVENT_RECORD> keyboardEvents);
};
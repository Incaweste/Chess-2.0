#pragma once

#include <memory>
#include <vector>

#include "AllChessPieces.h"
#include "BaseChessboard.h"
#include "ChessPiece.h"
#include "Utilits.h"

class Player
{
public:
    const bool IS_ON_WHITE_TEAM;
private:
    std::shared_ptr<BaseChessboard> _chessboard;
    std::vector<std::shared_ptr<ChessPiece>> _chessPieces;
    int _selectedPieceIndex = -1;

public:
    inline Player(bool isOnWhiteTeam, std::shared_ptr<BaseChessboard> chessboard);
    inline void ActivateSelection();
    inline void DeactivateSelection();
    inline void EraseNecessaryPieces();

    void GoToNextSelection(Utilits::DeltaMove direction);
private:
    void SetDefaultChessPiecesSetup();
};

#include "Player.inl"
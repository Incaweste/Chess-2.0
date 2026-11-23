#pragma once

#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
    Rook(const Key& constructorKey, bool isWhite)
    : ChessPiece{constructorKey, L'R', isWhite, 4}
    {
    }

protected:
    void InitializePathsForMoves() override
    {
        MoveModifiers rookMoveModifiers = MoveModifiers::MOVE_TO_EMPTY_CELL |  MoveModifiers::MOVE_WITH_CAPTURING;
        for (int i = 1; i <= 8; ++i)
        {
            _pathsForMoves[0].push_back(MovePosition{Vector2{-i, 0}, rookMoveModifiers});
            _pathsForMoves[1].push_back(MovePosition{Vector2{0, -i}, rookMoveModifiers});
            _pathsForMoves[2].push_back(MovePosition{Vector2{0, i}, rookMoveModifiers});
            _pathsForMoves[3].push_back(MovePosition{Vector2{i, 0}, rookMoveModifiers});
        }
    }
};
#pragma once

#include "ChessPiece.h"

class Bishop : public ChessPiece
{
public:
    Bishop(const Key& constructorKey, bool isWhite)
    : ChessPiece{constructorKey,  L'B', isWhite, 4}
    {}
    
private:
    void InitializePathsForMoves() override
    {
        MoveModifiers bishopMoveModifiers = MoveModifiers::MOVE_TO_EMPTY_CELL |  MoveModifiers::MOVE_WITH_CAPTURING;
        for (int i = 1; i <= 8; ++i)
        {
            _pathsForMoves[0].push_back(MovePosition{Vector2{-i, -i}, bishopMoveModifiers});
            _pathsForMoves[1].push_back(MovePosition{Vector2{-i, i}, bishopMoveModifiers});
            _pathsForMoves[2].push_back(MovePosition{Vector2{i, -i}, bishopMoveModifiers});
            _pathsForMoves[3].push_back(MovePosition{Vector2{i, i}, bishopMoveModifiers});
        }
    }
};
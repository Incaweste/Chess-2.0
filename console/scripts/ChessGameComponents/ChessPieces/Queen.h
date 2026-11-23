#pragma once

#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
    Queen(const Key& constructorKey, bool isWhite)
    : ChessPiece{constructorKey, L'Q', isWhite, 8}
    {}

private:
    void InitializePathsForMoves() override
    {
        MoveModifiers queenMoveModifiers = MoveModifiers::MOVE_TO_EMPTY_CELL |  MoveModifiers::MOVE_WITH_CAPTURING;
        for (int i = 1; i <= 8; ++i)
        {
            _pathsForMoves[0].push_back(MovePosition{Vector2{-i, -i}, queenMoveModifiers});
            _pathsForMoves[1].push_back(MovePosition{Vector2{-i, 0}, queenMoveModifiers});
            _pathsForMoves[2].push_back(MovePosition{Vector2{-i, i}, queenMoveModifiers});
            _pathsForMoves[3].push_back(MovePosition{Vector2{0, -i}, queenMoveModifiers});
            _pathsForMoves[4].push_back(MovePosition{Vector2{0, i}, queenMoveModifiers});
            _pathsForMoves[5].push_back(MovePosition{Vector2{i, -i}, queenMoveModifiers});
            _pathsForMoves[6].push_back(MovePosition{Vector2{i, 0}, queenMoveModifiers});
            _pathsForMoves[7].push_back(MovePosition{Vector2{i, i}, queenMoveModifiers});
        }
    }
};
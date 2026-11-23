#pragma once

#include "ChessPiece.h"

class King : public ChessPiece
{
public:
    King(const Key& constructorKey, bool isWhite)
    : ChessPiece{constructorKey, L'K', isWhite, 8}
    {
    }

private:
    void InitializePathsForMoves() override
    {
        MoveModifiers kingMoveModifiers = MoveModifiers::MOVE_TO_EMPTY_CELL |  MoveModifiers::MOVE_WITH_CAPTURING;
        _pathsForMoves[0] = {MovePosition{Vector2{-1, -1}, kingMoveModifiers}};
        _pathsForMoves[1] = {MovePosition{Vector2{-1, 0}, kingMoveModifiers}};
        _pathsForMoves[2] = {MovePosition{Vector2{-1, 1}, kingMoveModifiers}};
        _pathsForMoves[3] = {MovePosition{Vector2{0, -1}, kingMoveModifiers}};
        _pathsForMoves[4] = {MovePosition{Vector2{0, 1}, kingMoveModifiers}};
        _pathsForMoves[5] = {MovePosition{Vector2{1, -1}, kingMoveModifiers}};
        _pathsForMoves[6] = {MovePosition{Vector2{1, 0}, kingMoveModifiers}};
        _pathsForMoves[7] = {MovePosition{Vector2{1, 1}, kingMoveModifiers}};
    }
};
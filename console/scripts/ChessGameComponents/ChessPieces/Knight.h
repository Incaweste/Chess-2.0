#pragma once

#include "ChessPiece.h"

class Knight : public ChessPiece
{
public:
    Knight(const Key& constructorKey, bool isWhite)
    : ChessPiece{constructorKey, L'k', isWhite, 8}
    {}

private:
    void InitializePathsForMoves() override
    { 
        MoveModifiers knightMoveModifiers = MoveModifiers::MOVE_TO_EMPTY_CELL |  MoveModifiers::MOVE_WITH_CAPTURING; 
        _pathsForMoves[0] = {MovePosition{Vector2{-2, -1}, knightMoveModifiers}};
        _pathsForMoves[1] = {MovePosition{Vector2{-2, 1}, knightMoveModifiers}};
        _pathsForMoves[2] = {MovePosition{Vector2{-1, -2}, knightMoveModifiers}};
        _pathsForMoves[3] = {MovePosition{Vector2{-1, 2}, knightMoveModifiers}};
        _pathsForMoves[4] = {MovePosition{Vector2{1, -2}, knightMoveModifiers}};
        _pathsForMoves[5] = {MovePosition{Vector2{1, 2}, knightMoveModifiers}};
        _pathsForMoves[6] = {MovePosition{Vector2{2, -1}, knightMoveModifiers}};
        _pathsForMoves[7] = {MovePosition{Vector2{2, 1}, knightMoveModifiers}};
    }
};
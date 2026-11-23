#pragma once

#include "ChessPiece.h"

class Pawn : public ChessPiece
{
private:
    int _teamFactor;
public:
    Pawn(const Key& constructorKey, bool isWhite) 
    : ChessPiece{constructorKey, L'P', isWhite, 3}, _teamFactor{isWhite ? -1 : 1}
    {
    }

protected:
    void InitializePathsForMoves() override
    {
        _pathsForMoves[0] = {MovePosition{Vector2{_teamFactor, -1}, MoveModifiers::MOVE_WITH_CAPTURING}};
        _pathsForMoves[1] = {
            MovePosition{Vector2{_teamFactor, 0}, MoveModifiers::MOVE_TO_EMPTY_CELL}, 
            MovePosition{Vector2{2 * _teamFactor, 0}, MoveModifiers::MOVE_TO_EMPTY_CELL | MoveModifiers::CAN_BE_FIRST_ONLY}
        };
        _pathsForMoves[2] = {MovePosition{Vector2{_teamFactor, 1}, MoveModifiers::MOVE_WITH_CAPTURING}};
    }
};
#include "ChessPiece.h"

void ChessPiece::SetIsCapturable(bool isCapturable)
{
    if (isCapturable)
    {
        _pieceColor = CAPTURABLE_PIECE_COLOR;
        Blinkable::PushUpdatingBlinkable(this);
    }
    else
    {
        _pieceColor = _defaultPieceColor;
        Blinkable::EraseUpdatingBlinkable(this);
    }

    _isCapturable = isCapturable;
}

void ChessPiece::AddPiece(Line& line) const
{
    bool isSuccess = line.TrySetActiveColor(TextBlock::ColorTarget::TEXT, _pieceColor);
    line += _character;

    if (isSuccess)
        line.SetActiveColorToDefault(TextBlock::ColorTarget::TEXT);
}

void ChessPiece::Update()
{
    if (_isCapturable)
        _pieceColor = GetIsShining() ? CAPTURABLE_PIECE_COLOR : _defaultPieceColor ;
}
#pragma once

inline BaseBoardCell::BaseBoardCell(const RGB* cellColor, std::weak_ptr<ChessPiece> piece) : BaseBoardCell{cellColor} 
{
    SetPieceOnCell(piece);
}

inline std::shared_ptr<ChessPiece> BaseBoardCell::GetChessPiece() const noexcept
{
    return _piece.lock();
}

inline void BaseBoardCell::SetPieceOnCell(std::weak_ptr<ChessPiece> piece) noexcept
{
    _piece = piece;
}

inline void BaseBoardCell::RemovePieceFromCell() noexcept
{
    _piece.reset();
}
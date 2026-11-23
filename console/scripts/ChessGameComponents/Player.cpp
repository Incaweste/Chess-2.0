#include "Player.h"

void Player::GoToNextSelection(Utilits::DeltaMove direction)
{
    if(_selectedPieceIndex < 0 || static_cast<std::size_t>(_selectedPieceIndex) >= _chessPieces.size())
        return;

    int nextIndex = Utilits::FindNextPositionIndex<decltype(_chessPieces)::value_type>(
        _chessPieces, 
        _chessPieces[_selectedPieceIndex]->GetPosition(), 
        _chessboard->CHESSBOARD_SIZE,
        direction, 
        !IS_ON_WHITE_TEAM,
        [](const auto& piece){
            return piece->GetPosition();
    });
        
    if (nextIndex >= 0)
    {
        _selectedPieceIndex = nextIndex;
        _chessboard->SetSelectedCell(_chessPieces[_selectedPieceIndex]->GetPosition());   
    }
}

void Player::SetDefaultChessPiecesSetup()
{
    int rowOffset, offsetCoeff;
    const int chessBoardSize = _chessboard->GetChessboardSize();
    const int edgeLastIndex = chessBoardSize - 1;
    if (IS_ON_WHITE_TEAM)
    {
        rowOffset = edgeLastIndex;
        offsetCoeff = -1;
    }
    else
    {
        rowOffset = 0;
        offsetCoeff = 1;
    }
    _chessPieces.resize(16);
    _chessPieces[0] = ChessPiece::InitializeSharedChessPiece<Rook>(IS_ON_WHITE_TEAM);
    _chessPieces[1] = ChessPiece::InitializeSharedChessPiece<Knight>(IS_ON_WHITE_TEAM);
    _chessPieces[2] = ChessPiece::InitializeSharedChessPiece<Bishop>(IS_ON_WHITE_TEAM);
    _chessPieces[3] = ChessPiece::InitializeSharedChessPiece<Queen>(IS_ON_WHITE_TEAM);
    _chessPieces[4] = ChessPiece::InitializeSharedChessPiece<King>(IS_ON_WHITE_TEAM);
    _chessPieces[5] = ChessPiece::InitializeSharedChessPiece<Bishop>(IS_ON_WHITE_TEAM);
    _chessPieces[6] = ChessPiece::InitializeSharedChessPiece<Knight>(IS_ON_WHITE_TEAM);
    _chessPieces[7] = ChessPiece::InitializeSharedChessPiece<Rook>(IS_ON_WHITE_TEAM);

    Vector2 piecePosition = Vector2{rowOffset, 0};
    for (int i = 0; i < chessBoardSize; ++i)
    {
        piecePosition.col = IS_ON_WHITE_TEAM ? i : edgeLastIndex - i;
        _chessboard->SetPieceOnCell(_chessPieces[i], piecePosition, false);
    }
    
    piecePosition.row += offsetCoeff;
    for (int i = 8; i < _chessPieces.size(); ++i)
    {
        piecePosition.col = IS_ON_WHITE_TEAM ? i - 8 : edgeLastIndex - (i - 8);
        _chessPieces[i] = ChessPiece::InitializeSharedChessPiece<Pawn>(IS_ON_WHITE_TEAM);
        _chessboard->SetPieceOnCell(_chessPieces[i], piecePosition, false);
    }
}
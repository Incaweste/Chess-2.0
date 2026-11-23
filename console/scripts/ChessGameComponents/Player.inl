inline Player::Player(bool isOnWhiteTeam, std::shared_ptr<BaseChessboard> chessboard) : IS_ON_WHITE_TEAM{isOnWhiteTeam}, _chessboard{chessboard} 
{
    SetDefaultChessPiecesSetup();
}

inline void Player::ActivateSelection()
{
    if (_chessPieces.size() == 0)
        return;
    
    _selectedPieceIndex = 0;
    _chessboard->SetSelectedCell(_chessPieces[_selectedPieceIndex]->GetPosition());
}

inline void Player::DeactivateSelection()
{
    _selectedPieceIndex = -1;
    _chessboard->SetSelectedCell(Vector2{-1, -1});
}

inline void Player::EraseNecessaryPieces()
{
    std::erase_if(_chessPieces, [](const auto& value){
        return value->GetShouldItBeErased();
    });
}
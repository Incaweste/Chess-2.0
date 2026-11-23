#pragma once

constexpr ChessPiece::MoveModifiers operator|(
    ChessPiece::MoveModifiers first, 
    ChessPiece::MoveModifiers second
) noexcept
{
    return static_cast<ChessPiece::MoveModifiers>(
        static_cast<std::size_t>(first) | static_cast<std::size_t>(second)
    );
}

constexpr ChessPiece::MoveModifiers operator&(
    ChessPiece::MoveModifiers first, 
    ChessPiece::MoveModifiers second
) noexcept
{
    return static_cast<ChessPiece::MoveModifiers>(
        static_cast<std::size_t>(first) & static_cast<std::size_t>(second)
    );
}

struct ChessPiece::MovePosition
{
private:
    friend ChessPiece;
    Vector2 _position{0, 0};
    MoveModifiers _moveModifiers = MoveModifiers::MOVE_TO_EMPTY_CELL;

public:
    MovePosition() noexcept = default;

    constexpr MovePosition(Vector2 position, MoveModifiers moveModifiers) noexcept : 
        _position{position}, _moveModifiers{moveModifiers}
    {
    }

    constexpr Vector2 GetPosition() const noexcept
    {
        return _position;
    }

    constexpr void SetPosition(Vector2 position) noexcept
    {
        _position = position;
    }

    constexpr void SetMoveModifiers(MoveModifiers moveModifiers) noexcept
    {
        _moveModifiers = moveModifiers;
    }

    constexpr bool HasModifiers(MoveModifiers requiredModifiers) const noexcept
    {
        return (_moveModifiers & requiredModifiers) == requiredModifiers;
    }
};

class ChessPiece::Key final
{
    friend ChessPiece;
private:
    Key() noexcept = default;
};

constexpr ChessPiece::ChessPiece(
    [[maybe_unused]] const ChessPiece::Key& constructorKey, 
    wchar_t character, 
    bool isWhite, 
    std::size_t pathsForMovesCount
) : _character{character}, _isWhite{isWhite}
{
    if (isWhite == true) 
    {
        _pieceColor = _defaultPieceColor = &Color::WHITE;
    }
    else 
    {
        _pieceColor = _defaultPieceColor = &Color::BLACK;
    }

    _pathsForMoves.resize(pathsForMovesCount);
}

template <std::derived_from<ChessPiece> Piece>
std::unique_ptr<Piece> ChessPiece::InitializeUniqueChessPiece(bool isWhite)
{
    std::unique_ptr<Piece> newPiece = std::make_unique<Piece>(Key{}, isWhite);
    ChessPiece& base = *newPiece;
    base.InitializePathsForMoves();
    return newPiece;
}

template <std::derived_from<ChessPiece> Piece>
std::shared_ptr<Piece> ChessPiece::InitializeSharedChessPiece(bool isWhite)
{
    std::shared_ptr<Piece> newPiece = std::make_shared<Piece>(Key{}, isWhite);
    ChessPiece& base = *newPiece;
    base.InitializePathsForMoves();
    return newPiece;
}

constexpr bool ChessPiece::GetIsWhite() const noexcept
{
    return _isWhite;
}

constexpr const TextBlock::RGB* ChessPiece::GetColor() const noexcept
{
    return _pieceColor;
}

constexpr Vector2 ChessPiece::GetPosition() const noexcept
{
    return _position;
}

constexpr bool ChessPiece::GetHadFirstMove() const noexcept
{
    return _hadFirstMove;
}

constexpr bool ChessPiece::GetShouldItBeErased() const noexcept
{
    return _shouldBeErased;
}

constexpr std::size_t ChessPiece::GetCountOfFullPaths() const noexcept
{
    return _pathsForMoves.size();
}

constexpr std::span<const ChessPiece::MovePosition> ChessPiece::GetFullPathForMove(int pathForMoveIndex) const
{
    if (pathForMoveIndex < 0 || pathForMoveIndex >= _pathsForMoves.size())
        return {};
    else
        return _pathsForMoves[pathForMoveIndex];
}

constexpr void ChessPiece::SetPosition(Vector2 position, bool isPlayerMove) noexcept
{
    _position = position;
    if (isPlayerMove && !_hadFirstMove)
        _hadFirstMove = true;
}

constexpr void ChessPiece::SetErasureMark() noexcept
{
    _shouldBeErased = true;
}
#pragma once

#include <concepts>
#include <functional>
#include <memory>
#include <optional>
#include <ranges>
#include <vector>

#include "Blinkable.h"
#include "Console.h"
#include "TextBlock.h"
#include "Vector2.h"

class ChessPiece : public Blinkable
{
public:
    enum class MoveModifiers : std::size_t
    {
        MOVE_TO_EMPTY_CELL = 1ull << 0,
        MOVE_WITH_CAPTURING = 1ull << 1,
        CAN_BE_FIRST_ONLY = 1ull << 2,
        CONTINUE_DESPITE_FLAGS = 1ull << 3,
        CONTINUE_DESPITE_PIECES = 1ull << 4,
        CONTINUE_DESPITE_BORDERS = 1ull << 5
    };
    struct MovePosition;
    class Key;

private:
    using RGB = TextBlock::RGB;
    using Color = TextBlock::Color;
    using Line = TextBlock::Line;

protected:
    wchar_t _character{};
    bool _isWhite = true;
    const RGB* _pieceColor{};
    Vector2 _position{-1, -1};
    std::vector<std::vector<MovePosition>> _pathsForMoves;
    bool _hadFirstMove = false;
    bool _isCapturable = false;
    bool _shouldBeErased = false;

private:
    static constexpr const RGB* CAPTURABLE_PIECE_COLOR = &Color::RED;
    const RGB* _defaultPieceColor;
    bool _isAlive = true;

public:
    constexpr ChessPiece(const Key& constructorKey, wchar_t type, bool isWhite, std::size_t pathsForMovesCount);

    virtual ~ChessPiece() = default;
    
    template <std::derived_from<ChessPiece> Piece>
    static std::unique_ptr<Piece> InitializeUniqueChessPiece(bool isWhite);
    template <std::derived_from<ChessPiece> Piece>
    static std::shared_ptr<Piece> InitializeSharedChessPiece(bool isWhite);

    constexpr bool GetIsWhite() const noexcept;
    constexpr const RGB* GetColor() const noexcept;
    constexpr Vector2 GetPosition() const noexcept;
    constexpr bool GetHadFirstMove() const noexcept;
    constexpr bool GetShouldItBeErased() const noexcept;
    constexpr std::size_t GetCountOfFullPaths() const noexcept;
    constexpr std::span<const MovePosition> GetFullPathForMove(int pathForMoveIndex) const;
    constexpr void SetPosition(Vector2 position, bool isPlayerMove) noexcept;
    constexpr void SetErasureMark() noexcept;

    void SetIsCapturable(bool isCapturable);
    void AddPiece(Line& line) const;

    void Update() override;
protected:
    virtual void InitializePathsForMoves() = 0;
};

#include "ChessPiece.inl"
#pragma once
#include "BaseChessPiece.h"

class Pawn final : public BaseChessPiece
{
public:
    Pawn();
    explicit Pawn(bool isWhitePiece);
    Pawn(const Pawn& other);
    Pawn(Pawn&& other) noexcept;
    Pawn& operator=(const Pawn& other) = default;
    Pawn& operator=(Pawn&& other) noexcept = default;
    ~Pawn() override;
    std::string Describe() const override;
    std::unique_ptr<BaseChessPiece> Clone() const override;
};

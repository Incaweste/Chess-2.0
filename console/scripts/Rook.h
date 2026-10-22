#pragma once
#include "BaseChessPiece.h"

class Rook final : public BaseChessPiece
{
public:
    Rook();
    explicit Rook(bool isWhitePiece);
    Rook(const Rook& other);
    Rook(Rook&& other) noexcept;
    Rook& operator=(const Rook& other) = default;
    Rook& operator=(Rook&& other) noexcept = default;
    ~Rook() override;
    std::string Describe() const override;
    std::unique_ptr<BaseChessPiece> Clone() const override;
};

#include "Pawn.h"
#include <utility>

Pawn::Pawn() : BaseChessPiece(L'P', 1, true, "Pawn")
{
    std::wcout << L"Pawn was created (default)" << std::endl;
}

Pawn::Pawn(bool isWhitePiece) : BaseChessPiece(L'P', 1, isWhitePiece, "Pawn")
{
    std::wcout << L"Pawn was created (parameters)" << std::endl;
}

Pawn::Pawn(const Pawn& other) : BaseChessPiece(other)
{
    std::wcout << L"Pawn was copied" << std::endl;
}

Pawn::Pawn(Pawn&& other) noexcept : BaseChessPiece(std::move(other))
{
    std::wcout << L"Pawn was moved" << std::endl;
}

Pawn::~Pawn()
{
    std::wcout << L"Pawn was destroyed" << std::endl;
}

std::string Pawn::Describe() const
{
    return BaseChessPiece::Describe() + ", symbol = " + static_cast<char>(_wcharChessPiece);
}

std::unique_ptr<BaseChessPiece> Pawn::Clone() const
{
    return std::make_unique<Pawn>(*this);
}

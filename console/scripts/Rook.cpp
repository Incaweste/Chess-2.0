#include "Rook.h"
#include <utility>

Rook::Rook() : BaseChessPiece(L'R', 5, true, "Rook")
{
    std::wcout << L"Rook was created (default)" << std::endl;
}

Rook::Rook(bool isWhitePiece) : BaseChessPiece(L'R', 5, isWhitePiece, "Rook")
{
    std::wcout << L"Rook was created (parameters)" << std::endl;
}

Rook::Rook(const Rook& other) : BaseChessPiece(other)
{
    std::wcout << L"Rook was copied" << std::endl;
}

Rook::Rook(Rook&& other) noexcept : BaseChessPiece(std::move(other))
{
    std::wcout << L"Rook was moved" << std::endl;
}

Rook::~Rook()
{
    std::wcout << L"Rook was destroyed" << std::endl;
}

std::string Rook::Describe() const
{
    return std::string("Rook: symbol = ") + static_cast<char>(_wcharChessPiece) + ", index = " + std::to_string(GetIndexInChessboard());
}

std::unique_ptr<BaseChessPiece> Rook::Clone() const
{
    return std::make_unique<Rook>(*this);
}

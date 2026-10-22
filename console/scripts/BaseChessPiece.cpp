#include "BaseChessPiece.h"
#include <utility>

int BaseChessPiece::_createdPiecesCount = 0;

BaseChessPiece::BaseChessPiece(wchar_t wcharChessPiece, int chessPieceValue, bool isWhitePiece, const std::string& name) :
    _chessPieceValue{chessPieceValue}, _isWhitePiece{isWhitePiece}, _name{name},
    _position{std::make_shared<PiecePosition>()}, _wcharChessPiece{wcharChessPiece}
{
    ++_createdPiecesCount;
    std::wcout << L"BaseChessPiece was created" << std::endl;
}

BaseChessPiece::BaseChessPiece(const BaseChessPiece& other) :
    _chessPieceValue{other._chessPieceValue}, _isWhitePiece{other._isWhitePiece}, _name{other._name},
    _position{std::make_shared<PiecePosition>(PiecePosition{other.GetIndexInChessboard()})},
    _wcharChessPiece{other._wcharChessPiece}
{
    ++_createdPiecesCount;
    std::wcout << L"BaseChessPiece was copied" << std::endl;
}

BaseChessPiece::BaseChessPiece(BaseChessPiece&& other) noexcept :
    _chessPieceValue{other._chessPieceValue}, _isWhitePiece{other._isWhitePiece}, _name{std::move(other._name)},
    _position{std::move(other._position)}, _wcharChessPiece{other._wcharChessPiece}
{
    ++_createdPiecesCount;
    std::wcout << L"BaseChessPiece was moved" << std::endl;
}

BaseChessPiece::~BaseChessPiece()
{
    std::wcout << L"BaseChessPiece was destroyed" << std::endl;
}

BaseChessPiece& BaseChessPiece::operator=(const BaseChessPiece& other)
{
    if (this == &other)
        return *this;

    auto position = std::make_shared<PiecePosition>(PiecePosition{other.GetIndexInChessboard()});
    _name = other._name;
    _chessPieceValue = other._chessPieceValue;
    _isWhitePiece = other._isWhitePiece;
    _wcharChessPiece = other._wcharChessPiece;
    _position = std::move(position);
    return *this;
}

BaseChessPiece& BaseChessPiece::operator=(BaseChessPiece&& other) noexcept
{
    if (this == &other)
        return *this;

    _name = std::move(other._name);
    _chessPieceValue = other._chessPieceValue;
    _isWhitePiece = other._isWhitePiece;
    _wcharChessPiece = other._wcharChessPiece;
    _position = std::move(other._position);
    return *this;
}

wchar_t BaseChessPiece::GetWcharChessPiece() const
{
    return _wcharChessPiece;
}

int BaseChessPiece::GetChessPieceValue() const
{
    return _chessPieceValue;
}

int BaseChessPiece::GetIndexInChessboard() const
{
    return _position ? _position->index : -1;
}

bool BaseChessPiece::GetIsWhitePiece() const
{
    return _isWhitePiece;
}

const std::string& BaseChessPiece::GetName() const
{
    return _name;
}

void BaseChessPiece::SetIndexInChessboard(int newIndexInChessboard)
{
    if (!_position)
        _position = std::make_shared<PiecePosition>();
    _position->index = newIndexInChessboard;
}

int BaseChessPiece::GetCreatedPiecesCount()
{
    return _createdPiecesCount;
}

std::string BaseChessPiece::Describe() const
{
    return _name + ": value = " + std::to_string(_chessPieceValue) + ", is white = " + std::to_string(_isWhitePiece);
}

std::unique_ptr<BaseChessPiece> BaseChessPiece::ShallowCopy() const
{
    auto copy = Clone();
    copy->_position = _position;
    return copy;
}

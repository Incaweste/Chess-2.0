#include "Chessboard.h"

Chessboard::Chessboard(int edgeLength, int maxChessPiecesValue) : _edgeLength{edgeLength}, _maxChessPiecesValue{maxChessPiecesValue}
{
    _wcharChessboard.resize(_edgeLength * _edgeLength, ' ');
    std::wcout << L"Chessboard was created" << std::endl;
}

Chessboard::~Chessboard()
{
    std::wcout << L"Chessboard was destroyed" << std::endl;
}

std::vector<std::weak_ptr<BaseChessPiece>> Chessboard::GetWhiteChessPieces() const
{
    return _whiteChessPieces;
}

std::vector<std::weak_ptr<BaseChessPiece>> Chessboard::GetBlackChessPieces() const
{
    return _blackChessPieces;
}

void Chessboard::AddChessPiece(const std::weak_ptr<BaseChessPiece>& weakNewChessPiece)
{
    auto newChessPiece = GetRealPointerOfChessPiece(weakNewChessPiece);
    bool isWhitePiece = newChessPiece->GetIsWhitePiece();
    int chessPieceValue = newChessPiece->GetChessPieceValue();
    int& curChessPiecesValue = isWhitePiece? _whiteChessPiecesValue : _blackChessPiecesValue;

    if (curChessPiecesValue + chessPieceValue > _maxChessPiecesValue)
    {
        std::wcout<< newChessPiece->GetWcharChessPiece() << " piece is superfluous, _isWhitePeace = " << isWhitePiece << std::endl;
        return;
    }

    curChessPiecesValue += chessPieceValue;

    int pieceIndex;
    std::vector<std::weak_ptr<BaseChessPiece>>& weakCurChessPieces = isWhitePiece ? _whiteChessPieces : _blackChessPieces;
    int curChessPiecesVectorSize = weakCurChessPieces.size();

    if (isWhitePiece)
        pieceIndex = curChessPiecesVectorSize == 0 ? 0 : GetRealPointerOfChessPiece(weakCurChessPieces[curChessPiecesVectorSize - 1])->GetIndexInChessboard() + 1;
    else
        pieceIndex = curChessPiecesVectorSize == 0 ? _wcharChessboard.size() - 1 : GetRealPointerOfChessPiece(weakCurChessPieces[curChessPiecesVectorSize - 1])->GetIndexInChessboard() - 1;

    if (pieceIndex < 0 || pieceIndex >= static_cast<int>(_wcharChessboard.size()) || _wcharChessboard[pieceIndex] != ' ')
    {
        std::wcout<< newChessPiece->GetWcharChessPiece() << " piece is superfluous, _isWhitePeace = " << isWhitePiece << std::endl;
        return;
    }

    newChessPiece->SetIndexInChessboard(pieceIndex);
    weakCurChessPieces.push_back(weakNewChessPiece);
    _wcharChessboard[pieceIndex] = newChessPiece->GetWcharChessPiece();
}

void Chessboard::RemoveChessPiece(const std::weak_ptr<BaseChessPiece>& weakRemovingChessPiece)
{
    auto removingChessPiece = GetRealPointerOfChessPiece(weakRemovingChessPiece);
    bool isWhitePiece = removingChessPiece->GetIsWhitePiece();
    std::vector<std::weak_ptr<BaseChessPiece>>& weakCurChessPieces = isWhitePiece ? _whiteChessPieces : _blackChessPieces;
    std::vector<std::weak_ptr<BaseChessPiece>>::iterator weakNecessaryPiece = std::find_if(
        weakCurChessPieces.begin(), 
        weakCurChessPieces.end(), 
        [&removingChessPiece, this](const std::weak_ptr<BaseChessPiece>& item){
            return removingChessPiece == GetRealPointerOfChessPiece(item);
        });

    if (weakNecessaryPiece == weakCurChessPieces.end())
    {
        std::wcout << "That piece doesn't exist on the chessboard" << std::endl;
        return;
    }

    auto necessaryPiece = (*weakNecessaryPiece).lock();
    if (necessaryPiece == nullptr)
        throw std::runtime_error("An empty pointer in the vector.");
    int i = necessaryPiece->GetIndexInChessboard();

    if (isWhitePiece)
    {
        for (auto it = weakNecessaryPiece; it < weakCurChessPieces.end(); ++i, ++it)
            _wcharChessboard[i] = _wcharChessboard[i + 1];
    }
    else
        for (auto it = weakNecessaryPiece; it < weakCurChessPieces.end(); --i, ++it)
            _wcharChessboard[i] = _wcharChessboard[i - 1];
    _wcharChessboard[i] = ' ';
    

    std::vector<std::weak_ptr<BaseChessPiece>>::iterator newEnd = std::remove_if(
        weakCurChessPieces.begin(), 
        weakCurChessPieces.end(), 
        [&removingChessPiece, this] (const std::weak_ptr<BaseChessPiece>& item){
            return removingChessPiece == GetRealPointerOfChessPiece(item); 
        });
    weakCurChessPieces.erase(newEnd, weakCurChessPieces.end());
}

void Chessboard::Update() const
{
    PrintChessboard();
}

void Chessboard::PrintChessboard() const
{
	std::wcout << Parts::TOP_LEFT_CORNER;
	std::wcout << std::wstring(_edgeLength, Parts::HORIZONTAL_BORDER);
	std::wcout << Parts::TOP_RIGHT_CORNER << std::endl;

	for (int i = 0; i < _edgeLength; ++i)
	{
		std::wcout << Parts::VERTICAL_BORDER;
		std::copy(_wcharChessboard.begin() + i * _edgeLength, _wcharChessboard.begin() + (i + 1) * _edgeLength, std::ostream_iterator<wchar_t, wchar_t>(std::wcout));
		std::wcout << Parts::VERTICAL_BORDER << std::endl;
	}

	std::wcout << Parts::BOTTOM_LEFT_CORNER;
	std::wcout << std::wstring(_edgeLength, Parts::HORIZONTAL_BORDER);
	std::wcout << Parts::BOTTOM_RIGHT_CORNER << std::flush;
}

std::shared_ptr<BaseChessPiece> Chessboard::GetRealPointerOfChessPiece(const std::weak_ptr<BaseChessPiece>& weakChessPiece) const
{
    auto realChessPiece = weakChessPiece.lock();
    if (realChessPiece == nullptr)
        throw std::runtime_error("GetRealPointerOfChessPiece has got a empty pointer.");
    return realChessPiece;
}

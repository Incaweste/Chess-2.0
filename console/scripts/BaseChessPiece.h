#pragma once
#include <iostream>
#include <memory>
#include <string>
#include "PiecePosition.h"

class BaseChessPiece
{
private:
    int _chessPieceValue;
    bool _isWhitePiece;
    std::string _name;
    std::shared_ptr<PiecePosition> _position;
    static int _createdPiecesCount;
protected:
    wchar_t _wcharChessPiece;

    BaseChessPiece(wchar_t wcharChessPiece, int chessPieceValue, bool isWhitePiece, const std::string& name);
    BaseChessPiece(const BaseChessPiece& other);
    BaseChessPiece(BaseChessPiece&& other) noexcept;
public:
    virtual ~BaseChessPiece();
    BaseChessPiece& operator=(const BaseChessPiece& other);
    BaseChessPiece& operator=(BaseChessPiece&& other) noexcept;
    wchar_t GetWcharChessPiece() const;
    int GetChessPieceValue() const;
    int GetIndexInChessboard() const;
    bool GetIsWhitePiece() const;
    const std::string& GetName() const;
    void SetIndexInChessboard(int newIndexInChessboard);
    static int GetCreatedPiecesCount();
    virtual std::string Describe() const;
    virtual std::unique_ptr<BaseChessPiece> Clone() const = 0;
    std::unique_ptr<BaseChessPiece> ShallowCopy() const;
};

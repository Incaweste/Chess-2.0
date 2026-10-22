#include <fcntl.h>
#include <io.h>
#include <memory>
#include <utility>
#include "GameManagement.h"
#include "Pawn.h"
#include "Rook.h"

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);

    {
        std::wcout << L"-------CONSTRUCTORS-------" << std::endl;
        Pawn original;
        original.SetIndexInChessboard(8);
        Pawn copied(original);
        Pawn moved(std::move(copied));
        Pawn assigned(false);
        (assigned = original) = assigned;
        Pawn moveAssigned;
        moveAssigned = std::move(moved);
        std::wcout << L"Assigned index = " << assigned.GetIndexInChessboard()
            << L", moved index = " << moveAssigned.GetIndexInChessboard() << std::endl;

        std::wcout << L"-------COPIES-------" << std::endl;
        auto shallow = original.ShallowCopy();
        shallow->SetIndexInChessboard(16);
        std::wcout << L"Shallow: original = " << original.GetIndexInChessboard()
            << L", copy = " << shallow->GetIndexInChessboard() << std::endl;
        auto deep = original.Clone();
        deep->SetIndexInChessboard(24);
        std::wcout << L"Deep: original = " << original.GetIndexInChessboard()
            << L", copy = " << deep->GetIndexInChessboard() << std::endl;

        std::wcout << L"-------POLYMORPHISM-------" << std::endl;
        std::unique_ptr<BaseChessPiece> pieces[] = {std::make_unique<Pawn>(), std::make_unique<Rook>(false)};
        for (const auto& piece : pieces)
            std::wcout << piece->Describe().c_str() << std::endl;

        std::wcout << L"-------STRINGS-------" << std::endl;
        std::string description = pieces[0]->GetName() + " white";
        std::size_t separator = description.find(' ');
        std::string name = description.substr(0, separator);
        std::wcout << description.c_str() << L", name is Pawn = " << (name == "Pawn") << std::endl;

        std::wcout << L"-------BOARD-------" << std::endl;
        auto whitePawn = std::make_shared<Pawn>();
        auto blackRook = std::make_shared<Rook>(false);
        GameManagement gameManagement(8, 10);
        Chessboard& gameChessboard = gameManagement.GetChessboard();
        gameChessboard.AddChessPiece(whitePawn);
        gameChessboard.AddChessPiece(blackRook);
        gameChessboard.Update();
        std::wcout << std::endl;
    }

    std::wcout << L"Created pieces = " << BaseChessPiece::GetCreatedPiecesCount() << std::endl;
    return 0;
}

using System.Collections.Generic;
using System.Linq;

public class Chessboard
{
    private static class Parts
    {
        public const char HORIZONTAL_BORDER = '\u2550';
        public const char VERTICAL_BORDER = '\u2551';
        public const char TOP_LEFT_CORNER = '\u2554';
        public const char TOP_RIGHT_CORNER = '\u2557';
        public const char BOTTOM_LEFT_CORNER = '\u255A';
        public const char BOTTOM_RIGHT_CORNER = '\u255D';
    };

    private int _edgeLength;

    private int _maxChessPiecesValue;
    private int _whiteChessPiecesValue = 0;
    private int _blackChessPiecesValue = 0;
    private List<char> _charChessboard;

    public List<BaseChessPiece> WhiteChessPieces { get; private set; } = new List<BaseChessPiece>();
    public List<BaseChessPiece> BlackChessPieces { get; private set; } = new List<BaseChessPiece>();

    public Chessboard(int edgeLength, int maxChessPiecesValue)
    {
        _edgeLength = edgeLength;
        _maxChessPiecesValue = maxChessPiecesValue;

        _charChessboard = Enumerable.Repeat(' ', edgeLength * edgeLength).ToList();
    }
    public void AddChessPiece(BaseChessPiece newChessPiece)
    {
        ref int curChessPiecesValue = ref (newChessPiece.IsWhitePiece? ref _whiteChessPiecesValue : ref _blackChessPiecesValue);

        if (curChessPiecesValue + newChessPiece.ChessPieceValue > _maxChessPiecesValue)
        {
            Console.WriteLine(newChessPiece.CharChessPiece + " piece is superfluous, IsWhitePeace = " + newChessPiece.IsWhitePiece);
            return;
        }

        curChessPiecesValue += newChessPiece.ChessPieceValue;

        int pieceIndex;
        List<BaseChessPiece> curChessPieces = newChessPiece.IsWhitePiece ? WhiteChessPieces : BlackChessPieces;

        if (newChessPiece.IsWhitePiece)
            pieceIndex = curChessPieces.Count == 0 ? 0 : curChessPieces[curChessPieces.Count - 1].IndexInChessboard + 1;
        else
            pieceIndex = curChessPieces.Count == 0 ? _charChessboard.Count - 1 : curChessPieces[curChessPieces.Count - 1].IndexInChessboard - 1;

        if (pieceIndex < 0 || pieceIndex > _charChessboard.Count || _charChessboard[pieceIndex] != ' ')
        {
            Console.WriteLine(newChessPiece.CharChessPiece + " piece is superfluous, _isWhitePeace = " + newChessPiece.IsWhitePiece);
            return;
        }

        newChessPiece.IndexInChessboard = pieceIndex;
        curChessPieces.Add(newChessPiece);
        _charChessboard[pieceIndex] = newChessPiece.CharChessPiece;
    }
    public void RemoveChessPiece(BaseChessPiece removingChessPiece)
    {
        List<BaseChessPiece> curChessPieces = removingChessPiece.IsWhitePiece ? WhiteChessPieces : BlackChessPieces;
        
        int rmChessPieceIndex = curChessPieces.FindIndex(chessPiece => chessPiece == removingChessPiece);

        if (rmChessPieceIndex == -1)
        {
            Console.WriteLine("That piece doesn't exist on the chessboard");
            return;
        }

        int i = removingChessPiece.IndexInChessboard;

        if (removingChessPiece.IsWhitePiece)
        {
            for (int index = rmChessPieceIndex + 1; index < curChessPieces.Count; ++i, ++index)
                _charChessboard[i] = _charChessboard[i + 1];
        }
        else
            for (int index = rmChessPieceIndex + 1 + 1; index < curChessPieces.Count; --i, ++index)
                _charChessboard[i] = _charChessboard[i - 1];
        _charChessboard[i] = ' ';

        curChessPieces.RemoveAt(rmChessPieceIndex);
    }
    public void Update()
    {
        PrintChessboard();
    }
    public override string ToString() => $"This chessboard's edge length = {_edgeLength}";
    private void PrintChessboard()
    {
        Console.WriteLine(Parts.TOP_LEFT_CORNER + new string(Parts.HORIZONTAL_BORDER, _edgeLength)  + Parts.TOP_RIGHT_CORNER);

        for (int i = 0; i < _edgeLength; ++i)
        {
            Console.Write(Parts.VERTICAL_BORDER);
            Console.Write(_charChessboard.GetRange(i * _edgeLength, _edgeLength).ToArray());
            Console.WriteLine(Parts.VERTICAL_BORDER);
        }

        Console.WriteLine(Parts.BOTTOM_LEFT_CORNER + new string(Parts.HORIZONTAL_BORDER, _edgeLength) + Parts.BOTTOM_RIGHT_CORNER);
    }
};
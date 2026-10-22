public abstract class BaseChessPiece
{
    private PiecePosition _position;
    private static int _createdPiecesCount;
    protected char _charChessPiece;

    public char CharChessPiece => _charChessPiece;
    public int ChessPieceValue { get; private set; }
    public bool IsWhitePiece { get; private set; }
    public string Name { get; private set; }
    public int IndexInChessboard
    {
        get => _position.Index;
        set => _position.Index = value;
    }

    protected BaseChessPiece(char charChessPiece, int chessPieceValue, bool isWhitePiece, string name)
    {
        _charChessPiece = charChessPiece;
        ChessPieceValue = chessPieceValue;
        IsWhitePiece = isWhitePiece;
        Name = name;
        _position = new PiecePosition();
        ++_createdPiecesCount;
        Console.WriteLine("BaseChessPiece was created");
    }

    protected BaseChessPiece(BaseChessPiece other)
    {
        _charChessPiece = other._charChessPiece;
        ChessPieceValue = other.ChessPieceValue;
        IsWhitePiece = other.IsWhitePiece;
        Name = other.Name;
        _position = new PiecePosition { Index = other.IndexInChessboard };
        ++_createdPiecesCount;
        Console.WriteLine("BaseChessPiece was copied");
    }

    public static int GetCreatedPiecesCount() => _createdPiecesCount;

    public virtual string Describe() => $"{Name}: value = {ChessPieceValue}, is white = {IsWhitePiece}";

    public abstract BaseChessPiece Clone();

    public BaseChessPiece ShallowCopy()
    {
        ++_createdPiecesCount;
        return (BaseChessPiece)MemberwiseClone();
    }

    public override bool Equals(object? obj)
    {
        if (ReferenceEquals(this, obj))
            return true;

        return obj is BaseChessPiece other && GetType() == other.GetType()
            && CharChessPiece == other.CharChessPiece && ChessPieceValue == other.ChessPieceValue
            && IsWhitePiece == other.IsWhitePiece && Name == other.Name
            && IndexInChessboard == other.IndexInChessboard;
    }

    public override int GetHashCode() =>
        HashCode.Combine(GetType(), CharChessPiece, ChessPieceValue, IsWhitePiece, Name, IndexInChessboard);

    public override string ToString() => Describe();
}

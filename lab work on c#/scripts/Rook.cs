public sealed class Rook : BaseChessPiece
{
    public Rook() : base('R', 5, true, "Rook")
    {
        Console.WriteLine("Rook was created (default)");
    }

    public Rook(bool isWhitePiece) : base('R', 5, isWhitePiece, "Rook")
    {
        Console.WriteLine("Rook was created (parameters)");
    }

    public Rook(Rook other) : base(other)
    {
        Console.WriteLine("Rook was copied");
    }

    public override string Describe() => $"Rook: symbol = {_charChessPiece}, index = {IndexInChessboard}";

    public override BaseChessPiece Clone() => new Rook(this);
}

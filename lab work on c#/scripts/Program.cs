Console.OutputEncoding = System.Text.Encoding.UTF8;

using IssueLog log = new IssueLog("LOG");

Console.WriteLine("-------CONSTRUCTORS-------");
Pawn original = new Pawn();
original.IndexInChessboard = 8;
Pawn copied = new Pawn(original);
Console.WriteLine($"Copied index = {copied.IndexInChessboard}");

Console.WriteLine("-------COPIES-------");
BaseChessPiece shallow = original.ShallowCopy();
shallow.IndexInChessboard = 16;
Console.WriteLine($"Shallow: original = {original.IndexInChessboard}, copy = {shallow.IndexInChessboard}");
BaseChessPiece deep = original.Clone();
deep.IndexInChessboard = 24;
Console.WriteLine($"Deep: original = {original.IndexInChessboard}, copy = {deep.IndexInChessboard}");

Console.WriteLine("-------POLYMORPHISM-------");
BaseChessPiece[] pieces = {new Pawn(), new Rook(false)};
foreach (BaseChessPiece piece in pieces)
    Console.WriteLine(piece.Describe());

Console.WriteLine("-------STRINGS-------");
string description = pieces[0].Name + " white";
int separator = description.IndexOf(' ');
string name = description.Substring(0, separator);
Console.WriteLine($"{description}, name is Pawn = {name == "Pawn"}");

Console.WriteLine("-------EQUALITY-------");
BaseChessPiece equal = original.Clone();
Console.WriteLine($"Equal copies = {original.Equals(equal)}, same hash = {original.GetHashCode() == equal.GetHashCode()}");
equal.IndexInChessboard = 32;
Console.WriteLine($"After change = {original.Equals(equal)}, different type = {original.Equals(pieces[1])}");

Console.WriteLine("-------BOARD-------");
GameManagement gameManagement = new GameManagement(8, 10);
gameManagement.MainChessboard.AddChessPiece(new Pawn());
gameManagement.MainChessboard.AddChessPiece(new Rook(false));
gameManagement.MainChessboard.Update();

Console.WriteLine($"Created pieces = {BaseChessPiece.GetCreatedPiecesCount()}");
log.Write("Program end");

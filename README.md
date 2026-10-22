# Лабораторная работа 4. Наследование, C#

Основа: `retivykh's-labs/lab-03-csharp`. Иерархия: `BaseChessPiece` → `Pawn`, `Rook`.

Сборка и запуск из корня репозитория (Windows, .NET SDK 10):

```powershell
dotnet build "lab work on c#/ChessApp.csproj" -c Release
dotnet run --project "lab work on c#/ChessApp.csproj" -c Release --no-build --no-restore
```

Программа показывает наследование, копирование, сравнение фигур по содержимому и размещение на доске, затем завершается без ввода.
`MemberwiseClone()` делит `PiecePosition` с оригиналом; конструктор копирования и `Clone()` создают отдельную позицию.
В выводе: `Shallow: original = 16, copy = 16`, `Deep: original = 16, copy = 24`.
`using IssueLog` закрывает журнал при завершении программы.

Общий отчёт по C++ и C#: [report.pdf](report.pdf).

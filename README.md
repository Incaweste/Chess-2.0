# Лабораторная работа 4. Наследование, C++

Основа: `retivykh's-labs/lab-03-cpp`. Иерархия: `BaseChessPiece` → `Pawn`, `Rook`.

Сборка и запуск из корня репозитория (Windows, g++ с поддержкой C++20):

```powershell
cd console/scripts
g++ -std=c++20 main.cpp GameManagement.cpp Chessboard.cpp BaseChessPiece.cpp Pawn.cpp Rook.cpp -o app.exe
.\app.exe
```

Программа показывает конструкторы, копирование и перемещение, полиморфизм, обработку строк и размещение фигур на доске, затем завершается без ввода.
Поверхностная копия делит `PiecePosition` с оригиналом; конструктор копирования и `Clone()` создают отдельную позицию.
В выводе: `Shallow: original = 16, copy = 16`, `Deep: original = 16, copy = 24`.

Общий отчёт по C++ и C#: [report.pdf](report.pdf).

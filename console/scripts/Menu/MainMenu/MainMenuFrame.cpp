#include "MainMenuFrame.h"

void MainMenuFrame::PrintContent() const
{
    const auto& title = _window.GetTitle();
    const auto& items = _window.GetItems();

    int titleX = _shiftAlongX
        + 1
        + (_totalWidth - static_cast<int>(title.length())) / 2;

    Console::MoveCaret(titleX, _shiftAlongY + 2);
    std::wcout << title;

    for (size_t i = 0; i < items.size(); ++i)
    {
        int itemX = _shiftAlongX + 3;
        int itemY = _shiftAlongY + 4 + static_cast<int>(i);

        Console::MoveCaret(itemX, itemY);
        std::wcout << items[i];
    }

    std::wcout << std::flush;
}
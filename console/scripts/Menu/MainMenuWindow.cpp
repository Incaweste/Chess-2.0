#include "MainMenuWindow.h"

MainMenuWindow::MainMenuWindow()
{
    _items = {
        L"Начать игру",
        L"Инвентарь",
        L"Магазин",
        L"Управление",
        L"Выход",
    };
    _countRows = _items.size();
    _title = L"Chess 2.0";
    _maxWidth = 15;
}

MainMenuWindow::~MainMenuWindow() = default;

const std::wstring MainMenuWindow::GetTitle() const
{
    return _title;
}

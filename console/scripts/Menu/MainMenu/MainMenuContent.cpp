#include "MainMenuContent.h"

MainMenuContent::MainMenuContent() : InfoWindowBase()
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
}

MainMenuContent::~MainMenuContent() = default;




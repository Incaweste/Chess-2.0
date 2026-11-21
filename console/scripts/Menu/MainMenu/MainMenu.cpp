#include "MainMenu.h"

MainMenu::MainMenu() : InfoWindowBase()
{
    _items = {
        { L"Start game", MenuAction::StartGame },
        //{ L"Inventory", MenuAction::Inventory },
        //{ L"Shop", MenuAction::Shop },
        //{ L"Controls", MenuAction::Controls },
        { L"Exit", MenuAction::Exit },
    };

    _title = L"Chess 2.0";

    _totalWidth = GetMaxWidth() + _LEFT_RIGHT_INDENTS;
    _totalHeight = _items.size() + _UP_BOTTOM_INDENTS;

    _boundaryIndices = {1};
}

void MainMenu::Update()
{
    if (_isActive) 
    {
        PrintFrame();
        PrintContent();
    }
}

int MainMenu::GetMaxWidth() const
{
    size_t maxLength = 0;

    for (const auto& item : _items)
    {
        if (item.text.length() > maxLength)
            maxLength = item.text.length();
    }

    maxLength = (_title.length() > maxLength) ? _title.length() : maxLength;

    return maxLength;
}

void MainMenu::PrintContent() const
{
    const int titleX = _shiftAlongX + 1
        + (_totalWidth - _title.length()) / 2;

    Console::MoveCaret(titleX, _shiftAlongY + 1);
    std::wcout << _title;

    const int itemX = _shiftAlongX + 2;

    for (int i = 0; i < _items.size(); ++i)
    {
        Console::MoveCaret(itemX, _shiftAlongY + 3 + i);
        std::wcout << (i == _selectedIndex ? L'>' : L' ') << _items[i].text;
    }

    std::wcout << std::flush;
}

std::optional<MenuAction> MainMenu::HandleMenuSelect()
{
    if (_kbhit())
    {
        int key = _getch();

        if (key == Keys::SPECIAL_1 || 
            key == Keys::SPECIAL_2)
        {
            key = _getch();

            if (key == Keys::ARROW_UP)
            {
                if (_selectedIndex > 0)
                    --_selectedIndex;
            }
            if (key == Keys::ARROW_DOWN)
            {
                if (_selectedIndex < (_items.size()-1))
                    ++_selectedIndex;
            }
        }
        else if (key == Keys::ENTER)
        {
            return SelectItem();
        }
    }
    return std::nullopt;
}

std::optional<MenuAction> MainMenu::SelectItem() const
{
    if (_selectedIndex >= 0 && _selectedIndex < _items.size())
        return _items[_selectedIndex].action;

    return std::nullopt;
}
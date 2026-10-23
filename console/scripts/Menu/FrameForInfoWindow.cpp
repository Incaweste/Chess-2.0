#include "FrameForInfoWindow.h"

FrameForInfoWindow::~FrameForInfoWindow() = default;

FrameForInfoWindow::FrameForInfoWindow(const InfoWindowBase& window, bool isActive)
    : _window{window},
    _isActive{isActive}, 
    _countRows{window.GetCountRows()},
    _titleLength{window.GetTitleLength()}
{
    short spaceLeftAboveInterval = 2;
    short aboveRightBelowInterval = 2;
    _totalHeight = _countRows + spaceLeftAboveInterval + aboveRightBelowInterval;
    _totalWidth = window.GetMaxWidth() + spaceLeftAboveInterval + aboveRightBelowInterval;
}

void FrameForInfoWindow::Update()
{
    if (_isActive) 
    {
        PrintFrame();
        PrintContent();
    }
}

void FrameForInfoWindow::MoveCaret(int shiftAlongX, int shiftAlongY) const
{
    std::wcout << L"\033["
    << shiftAlongY
    << ';'
    << shiftAlongX
    << "H" << std::flush;
}

void FrameForInfoWindow::SetShift(int shiftAlongX, int shiftAlongY)
{
    _shiftAlongX = shiftAlongX;
    _shiftAlongY = shiftAlongY;
}

void FrameForInfoWindow::PrintFrame() const
{
    MoveCaret(_shiftAlongX, _shiftAlongY);

    std::wcout << FrameParts::TOP_LEFT_CORNER
        << std::wstring(_totalWidth, FrameParts::TOP_BORDER)
        << FrameParts::TOP_RIGHT_CORNER;

    for (int i = 0; i < _totalHeight; ++i)
    {
        MoveCaret(_shiftAlongX, _shiftAlongY + 1 + i);

        std::wcout << FrameParts::LEFT_BORDER;
        MoveCaret(_shiftAlongX+_totalWidth+1, _shiftAlongY + 1 + i);
        std::wcout << FrameParts::RIGHT_BORDER;
    }

    MoveCaret(_shiftAlongX, _shiftAlongY + _totalHeight + 1);

    std::wcout << FrameParts::BOTTOM_LEFT_CORNER
        << std::wstring(_totalWidth, FrameParts::BOTTOM_BORDER)
        << FrameParts::BOTTOM_RIGHT_CORNER
        << std::flush;
}

void FrameForInfoWindow::PrintContent() const
{
    // Debug
    const auto& title = _window.GetTitle();
    const auto& items = _window.GetItems();

    int titleX = _shiftAlongX
        + 1
        + (_totalWidth - static_cast<int>(title.length())) / 2;

    MoveCaret(titleX, _shiftAlongY + 2);
    std::wcout << title;

    for (size_t i = 0; i < items.size(); ++i)
    {
        int itemX = _shiftAlongX + 3;
        int itemY = _shiftAlongY + 4 + static_cast<int>(i);

        MoveCaret(itemX, itemY);
        std::wcout << items[i];
    }

    std::wcout << std::flush;
}
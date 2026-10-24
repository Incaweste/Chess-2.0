#include "FrameForInfoWindow.h"

FrameForInfoWindow::~FrameForInfoWindow() = default;

FrameForInfoWindow::FrameForInfoWindow(const InfoWindowBase& window, bool isActive)
    : _window{window},
    _isActive{isActive}, 
    _countWindowRows{window.GetCountRows()},
    _titleLength{window.GetTitleLength()}
{
    short spaceLeftAboveInterval = 2;
    short aboveRightBelowInterval = 2;
    _totalHeight = _countWindowRows + spaceLeftAboveInterval + aboveRightBelowInterval;
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

void FrameForInfoWindow::SetShift(int shiftAlongX, int shiftAlongY)
{
    _shiftAlongX = shiftAlongX;
    _shiftAlongY = shiftAlongY;
}

void FrameForInfoWindow::PrintFrame() const
{
    Console::MoveCaret(_shiftAlongX, _shiftAlongY);

    std::wcout << FrameParts::TOP_LEFT_CORNER
        << std::wstring(_totalWidth, FrameParts::TOP_BORDER)
        << FrameParts::TOP_RIGHT_CORNER;

    for (int i = 0; i < _totalHeight; ++i)
    {
        Console::MoveCaret(_shiftAlongX, _shiftAlongY + 1 + i);

        std::wcout << FrameParts::LEFT_BORDER;
        Console::MoveCaret(_shiftAlongX+_totalWidth+1, _shiftAlongY + 1 + i);
        std::wcout << FrameParts::RIGHT_BORDER;
    }

    Console::MoveCaret(_shiftAlongX, _shiftAlongY + _totalHeight + 1);

    std::wcout << FrameParts::BOTTOM_LEFT_CORNER
        << std::wstring(_totalWidth, FrameParts::BOTTOM_BORDER)
        << FrameParts::BOTTOM_RIGHT_CORNER
        << std::flush;
}
#include "InfoWindowBase.h"

InfoWindowBase::~InfoWindowBase() = default;

InfoWindowBase::InfoWindowBase(bool isActive)
    : _isActive{isActive} {}

void InfoWindowBase::NowActive()
{
    _isActive = true;
}

int InfoWindowBase::GetRequiredWidth() const
{
	return _shiftAlongX + _totalWidth + VIEWPORT_PADDING;
}

int InfoWindowBase::GetRequiredHeight() const
{
	return _shiftAlongY + _totalHeight + VIEWPORT_PADDING;
}

void InfoWindowBase::SetShift(int shiftAlongX, int shiftAlongY)
{
    _shiftAlongX = shiftAlongX;
    _shiftAlongY = shiftAlongY;
}

void InfoWindowBase::PrintFrame() const
{
    Console::MoveCaret(_shiftAlongX, _shiftAlongY);

    std::wcout << FrameParts::TOP_LEFT_CORNER
        << std::wstring(_totalWidth, FrameParts::HORIZONTAL_BORDER)
        << FrameParts::TOP_RIGHT_CORNER;

    for (int i = 0; i < _totalHeight; ++i)
    {
        Console::MoveCaret(_shiftAlongX, _shiftAlongY + 1 + i);

        bool hasBoundary = std::find(
            _boundaryIndices.begin(),
            _boundaryIndices.end(),
            i
        ) != _boundaryIndices.end();

        if (hasBoundary)
        {
            std::wcout << FrameParts::BOUNDARY_LEFT;
            std::wcout << std::wstring(_totalWidth, FrameParts::HORIZONTAL_BORDER);
            std::wcout << FrameParts::BOUNDARY_RIGHT;
        }
        else 
        {
            std::wcout << FrameParts::VERTICAL_BORDER;
            Console::MoveCaret(_shiftAlongX+_totalWidth+1, _shiftAlongY + 1 + i);
            std::wcout << FrameParts::VERTICAL_BORDER;
        }
    }

    Console::MoveCaret(_shiftAlongX, _shiftAlongY + _totalHeight + 1);

    std::wcout << FrameParts::BOTTOM_LEFT_CORNER
        << std::wstring(_totalWidth, FrameParts::HORIZONTAL_BORDER)
        << FrameParts::BOTTOM_RIGHT_CORNER
        << std::flush;
}
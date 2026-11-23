#include "TextBlock.h"

void TextBlock::SetActiveColorForSeveralLines(
    std::size_t startIndex, 
    std::size_t linesCount,
    ColorTarget target,
    const RGB* color
)
{
    std::size_t maxLinesCount = _lines.size();
    if (startIndex < maxLinesCount)
    {
        std::size_t endIndex = startIndex + linesCount;
        if (endIndex > maxLinesCount)
            endIndex = maxLinesCount;

        for (std::size_t i = startIndex; i < endIndex; ++i)
            _lines[i].TrySetActiveColor(target, color);
    }
}

void TextBlock::SetActiveColorForAllLines(ColorTarget target, const RGB* color)
{
    SetActiveColorForSeveralLines(0, _lines.size(), target, color);
}

bool TextBlock::Line::TrySetActiveColor(ColorTarget target, const RGB* activeColor)
{
    return GetColorHandler(target).TrySetActiveColor(*this, activeColor);
}

void TextBlock::Line::SetActiveColorToDefault(ColorTarget target)
{
    GetColorHandler(target).SetActiveColorToDefault(*this);
}

void TextBlock::Line::ResetActiveColor(ColorTarget target)
{
    GetColorHandler(target).ResetActiveColor(*this);
}

void TextBlock::Line::ColorHandler::SetActiveColorToDefault(Line& handlingLine)
{
    if (_defaultColor != nullptr)
        TrySetActiveColor(handlingLine, _defaultColor);
    else
        ResetActiveColor(handlingLine);
}

bool  TextBlock::Line::ColorHandler::TrySetActiveColor(Line& handlingLine, const RGB* activeColor)
{
    if (activeColor != nullptr && activeColor != _activeColor)
    {
        _activeColor = activeColor;

        std::wostringstream wstrStream{std::ios_base::openmode::_S_out | std::ios_base::openmode::_S_app};
        wstrStream
            << L"\x1b" << _setColorCommand
            << _activeColor->r << L';'
            << _activeColor->g << L';'
            << _activeColor->b << L'm';
        handlingLine += wstrStream.str();
        return true;
    }
    else
        return false;
}

void  TextBlock::Line::ColorHandler::ResetActiveColor(Line& handlingLine)
{
    handlingLine += L"\033" + _resetColorCommand;
    _activeColor = nullptr;
}
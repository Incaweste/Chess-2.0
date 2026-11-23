#pragma once

constexpr TextBlock::TextBlock(
    std::size_t linesCount, 
    std::size_t oneLineLength,
    const RGB* defaultTextColor, 
    const RGB* defaultBGColor, 
    bool areColorsAlreadySetted, 
    std::size_t gapBefore
) : gapBefore{gapBefore}
{
    _lines.reserve(linesCount);
    for (std::size_t i = 0; i < linesCount; ++i)
    {
        _lines.emplace_back(defaultTextColor, defaultBGColor, areColorsAlreadySetted, oneLineLength);
        if (!areColorsAlreadySetted)
        {
            _lines[i].SetActiveColorToDefault(ColorTarget::TEXT);
            _lines[i].SetActiveColorToDefault(ColorTarget::BACKGROUND);
        }
    }
}

constexpr TextBlock::TextBlock(
    std::size_t linesCount, 
    const RGB* defaultTextColor, 
    const RGB* defaultBGColor, 
    bool areColorsAlreadySetted, 
    std::size_t gapBefore
) : TextBlock{linesCount, 0, defaultTextColor, defaultBGColor, areColorsAlreadySetted, gapBefore}
{
}

constexpr TextBlock::TextBlock(
    std::size_t linesCount, 
    std::size_t oneLineLength,
    const RGB* defaultTextColor, 
    const RGB* defaultBGColor, 
    bool areColorsAlreadySetted
) : 
    TextBlock{linesCount, oneLineLength, defaultTextColor, defaultBGColor, areColorsAlreadySetted, 0}
{
}

constexpr TextBlock::TextBlock(
    std::size_t linesCount, 
    const RGB* defaultTextColor, 
    const RGB* defaultBGColor, 
    bool areColorsAlreadySetted
) : 
    TextBlock{linesCount, defaultTextColor, defaultBGColor, areColorsAlreadySetted, 0}
{
}

constexpr TextBlock::TextBlock(std::size_t linesCount, std::size_t oneLineLength, std::size_t gapBefore) : 
    TextBlock{linesCount, oneLineLength, {}, {}, false, gapBefore}
{
}

constexpr TextBlock::TextBlock(std::size_t linesCount, std::size_t oneLineLength) : TextBlock{linesCount, oneLineLength, 0}
{
}

constexpr TextBlock::TextBlock(std::size_t linesCount) : TextBlock{linesCount, 0}
{
}

constexpr TextBlock::Line& TextBlock::operator[](std::size_t index)
{
    return _lines[index];
}

constexpr const TextBlock::Line& TextBlock::operator[](std::size_t index) const
{
    return _lines[index];
}
constexpr auto TextBlock::begin() const noexcept
{
    return _lines.begin();
}

constexpr auto TextBlock::end() const noexcept
{
    return _lines.end();
}

constexpr auto TextBlock::begin() noexcept
{
    return _lines.begin();
}

constexpr auto TextBlock::end() noexcept
{
    return _lines.end();
}

constexpr std::size_t TextBlock::GetLinesCount() const noexcept
{
    return _lines.size();
}

constexpr void TextBlock::AddCharsForSeveralLines(
    std::size_t startIndex, 
    std::size_t linesCount, 
    std::size_t charsCount, 
    wchar_t character)
{
    std::size_t maxLinesCount = _lines.size();
    if (startIndex < maxLinesCount)
    {
        std::size_t endIndex = startIndex + linesCount;
        if (endIndex > maxLinesCount)
            endIndex = maxLinesCount;

        for (std::size_t i = startIndex; i < endIndex; ++i)
            _lines[i].AddChars(charsCount, character);
    }
}

constexpr void TextBlock::AddCharsForAllLines(std::size_t charsCount, wchar_t character)
{
    AddCharsForSeveralLines(0, _lines.size(), charsCount, character);
}

constexpr void TextBlock::AddLines(std::size_t count)
{
    for(std::size_t i = 0; i < count; ++i)
        _lines.emplace_back();
}

constexpr void TextBlock::RemoveLines(std::size_t startIndex, std::size_t count)
{
    std::size_t linesSize = _lines.size();
    if (count > 0 && startIndex < linesSize)
    {
        if (count > 1)
        {
            std::size_t lastIndex = startIndex + count;
            std::vector<Line>::iterator firstIt = _lines.begin(), lastIt;
            lastIt = lastIndex > linesSize ? _lines.end() : firstIt + lastIndex;
            _lines.erase(firstIt, lastIt);
        }
        else
            _lines.erase(_lines.begin());
    }
}

constexpr void TextBlock::MergeWithTextBlock(const TextBlock& mergingLines, std::size_t startIndexInMain)
{
    std::size_t mainLinesCount = _lines.size();
    std::size_t mergingLinesCount = mergingLines._lines.size();
    if (startIndexInMain + mergingLinesCount > mainLinesCount)
    {
        if(startIndexInMain > mainLinesCount)
            startIndexInMain = mainLinesCount;

        for (std::size_t i = mergingLinesCount - (mainLinesCount - startIndexInMain); i > 0; --i)
            _lines.emplace_back();
    }

    for (std::size_t i = 0; i < mergingLinesCount; ++i)
        _lines[startIndexInMain + i] += mergingLines._lines[i];
}
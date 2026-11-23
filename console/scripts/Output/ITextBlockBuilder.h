#pragma once

#include "TextBlock.h"

class ITextBlockBuilder
{
public:
    virtual ~ITextBlockBuilder() noexcept = default;
    TextBlock virtual BuildTextBlock(const TextBlock::RGB* outsideTextColor, const TextBlock::RGB* outsideBGColor) const = 0;
};
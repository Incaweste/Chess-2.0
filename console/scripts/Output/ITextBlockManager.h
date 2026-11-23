#pragma once

#include "ITextBlockBuilder.h"
#include "Vector2.h"

class ITextBlockManager : ITextBlockBuilder
{
public:
    virtual ~ITextBlockManager() noexcept = default;
    virtual Vector2 GetSizeInChars() const noexcept = 0;
};
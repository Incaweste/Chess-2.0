#pragma once

#include <optional>

#include "MenuAction.h"

class IMenuInput
{
public:
    virtual ~IMenuInput() = default;
    virtual std::optional<MenuAction> HandleMenuSelect() = 0;
};
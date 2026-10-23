#pragma once

#include <string>

#include "InfoWindowBase.h"

class MainMenuWindow : public InfoWindowBase
{
public:
    MainMenuWindow();
    ~MainMenuWindow();

    const std::wstring GetTitle() const; // ?
};
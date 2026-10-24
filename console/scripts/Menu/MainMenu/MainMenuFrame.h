#pragma once

#include "FrameForInfoWindow.h"

class MainMenuFrame : public FrameForInfoWindow
{
public:
    using FrameForInfoWindow::FrameForInfoWindow;

    void PrintContent() const override;
};
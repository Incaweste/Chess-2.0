#pragma once

#include <iostream>

#include "AllMenuWindows.h"
#include "IUpdatable.h"

class FrameForInfoWindow : public IUpdatable
{
private:
    bool _isActive;
    const InfoWindowBase& _window;
    int _totalWidth = 20;
    int _countRows = 6;
    int _titleLength = 14;
    int _totalHeight = 10;
    int _shiftAlongX = 1;
    int _shiftAlongY = 1;

public:
    FrameForInfoWindow(const InfoWindowBase& window, bool isActive = true);
    ~FrameForInfoWindow();

    void PrintContent() const;
    void Update() override;
    void PrintFrame() const;
    void MoveCaret(int shiftAlongX, int shiftAlongY) const;
    void SetShift(int shiftAlongX, int shiftAlongY);

private:
    struct FrameParts final
    {
        static inline constexpr wchar_t TOP_BORDER = L'\u2580';  
        static inline constexpr wchar_t BOTTOM_BORDER = L'\u2584';  
        static inline constexpr wchar_t RIGHT_BORDER = L'\u2590';  
        static inline constexpr wchar_t LEFT_BORDER = L'\u258C';  
        static inline constexpr wchar_t TOP_LEFT_CORNER = L'\u259B';  
        static inline constexpr wchar_t TOP_RIGHT_CORNER = L'\u259C';  
        static inline constexpr wchar_t BOTTOM_LEFT_CORNER = L'\u2599';  
        static inline constexpr wchar_t BOTTOM_RIGHT_CORNER = L'\u259F';
    
        virtual ~FrameParts() = 0;
    };
};
#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <optional>
#include <conio.h>

#include "IUpdatable.h"
#include "Console.h"
#include "MenuAction.h"

class InfoWindowBase : public IUpdatable
{
protected:
    int _totalWidth;
    int _totalHeight;

    int _shiftAlongX = 1;
    int _shiftAlongY = 1;

    std::vector<int> _boundaryIndices;

    bool _isActive;

    static inline constexpr int VIEWPORT_PADDING = 4;

public:
    explicit InfoWindowBase(bool isActive = true);
    virtual ~InfoWindowBase();

    int GetRequiredWidth() const;
    int GetRequiredHeight() const;

    virtual void PrintContent() const = 0;

    void PrintFrame() const;
    void SetShift(int shiftAlongX, int shiftAlongY);

    void NowActive(); //?

private:
    struct FrameParts final
    {
        static inline constexpr wchar_t HORIZONTAL_BORDER = L'\u2501';
        static inline constexpr wchar_t VERTICAL_BORDER = L'\u2503';
        static inline constexpr wchar_t BOUNDARY_LEFT = L'\u2523';
        static inline constexpr wchar_t BOUNDARY_RIGHT = L'\u252B';
        static inline constexpr wchar_t BOUNDARY_TOP = L'\u2533';
        static inline constexpr wchar_t BOUNDARY_BOTTOM = L'\u253B';
        static inline constexpr wchar_t TOP_LEFT_CORNER = L'\u250F';
        static inline constexpr wchar_t TOP_RIGHT_CORNER = L'\u2513';
        static inline constexpr wchar_t BOTTOM_LEFT_CORNER = L'\u2517';
        static inline constexpr wchar_t BOTTOM_RIGHT_CORNER = L'\u251B';
    
        virtual ~FrameParts() = 0;
    };

};
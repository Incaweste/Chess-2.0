#pragma once

#include <iostream>
#include <windows.h>

#undef RGB

class Console
{
public:
    struct Color;

    struct RGB final
    {
        int r;
        int g;
        int b;

    private:
        friend struct Color;
        RGB(int r, int g, int b);
        RGB(const RGB& other);
        RGB(RGB&& other);
    };
    
    struct Color final
    {
        static inline const RGB BLACK = {0, 0, 0};
        static inline const RGB BLUE = {0, 0, 255};
        static inline const RGB CYAN = {0, 255, 255};
        static inline const RGB GRAY = {128, 128, 128};
        static inline const RGB GREEN = {0, 255, 0};
        static inline const RGB LIGHT_BLUE = {173, 216, 230};
        static inline const RGB LIGHT_CYAN = {224, 255, 255};
        static inline const RGB LIGHT_GREEN = {144, 238, 144};
        static inline const RGB LIGHT_MAGENTA = {255, 182, 255};
        static inline const RGB LIGHT_RED = {255, 182, 193};
        static inline const RGB LIGHT_YELLOW = {255, 255, 182};
        static inline const RGB MAGENTA = {255, 0, 255};
        static inline const RGB RED = {255, 0, 0};
        static inline const RGB WHITE = {255, 255, 255};
        static inline const RGB YELLOW = {255, 255, 0};

        virtual ~Color() = 0;
    };

private:
    static inline const HANDLE _OUTPUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
public:
    virtual ~Console() = 0;

    static void SetTextColor(const RGB* Color);
    static void SetBGColor(const RGB* Color);
    static void ResetConsoleColor();

    static void ResetCaret();
    static void MoveCaret(int shiftAlongX, int shiftAlongY);
    static void RefreshConsole();
    static bool IsThisFitInConsole(int rowCnt, int colCnt);
};


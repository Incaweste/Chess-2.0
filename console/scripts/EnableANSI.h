#pragma once

#include <windows.h>
#include <io.h>
#include <fcntl.h>

inline bool EnableConsoleUnicodeAndANSI()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE || hOut == nullptr)
        return false;

    DWORD mode = 0;
    if (!GetConsoleMode(hOut, &mode))
        return false;

    bool ok = true;

    if (!SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING))
        ok = false;

    if (_setmode(_fileno(stdout), _O_U16TEXT) == -1 ||
        _setmode(_fileno(stderr), _O_U16TEXT) == -1 ||
        _setmode(_fileno(stdin), _O_U16TEXT) == -1) 
        ok = false;

    return ok;
}
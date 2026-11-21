//DON'T EDIT
#include <stdexcept>

#include "GameManagement.h"
#include "EnableANSI.h"
#include "Cursor.h"

int main()
{
    if (!EnableConsoleUnicodeAndANSI())
    {
        throw std::runtime_error("Failed to enable console Unicode and ANSI support.");
    }
    HideCursor();

    GameManagement& gameManagement = GameManagement::GetGameManagement();
    gameManagement.Update();

    ShowCursor();
    return 0;
}
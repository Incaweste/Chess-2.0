//DON'T EDIT
#include <io.h>
#include <fcntl.h>
#include <stdexcept>

#include "GameManagement.h"

int main()
{
	if (_setmode(_fileno(stdout), _O_U16TEXT) == -1)
        throw std::runtime_error("_O_U16TEXT mode didn't set.");

    GameManagement& gameManagement = GameManagement::GetGameManagement();
    gameManagement.StartGame();
    gameManagement.Update();
    return 0;
}
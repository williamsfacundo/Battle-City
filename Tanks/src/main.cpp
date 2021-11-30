#include "game/game.h"

#include <iostream>
#include <time.h>

using namespace Battle_City;

int main()
{
    srand(time(NULL));

    Game* game = new Game();

    game->Run();

    delete game;

    return 0;
}
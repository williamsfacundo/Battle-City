#include "gameplay/gameplay.h"

#include <iostream>
#include <time.h>

using namespace Battle_City;

int main()
{
    srand(time(NULL));

    Gameplay* gameplay = new Gameplay();

    gameplay->Run();

    delete gameplay;

    return 0;
}
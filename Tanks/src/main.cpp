#include "gameplay/gameplay.h"

using namespace Battle_City;

int main()
{
    Gameplay* gameplay = new Gameplay();

    gameplay->Run();

    delete gameplay;

    return 0;
}
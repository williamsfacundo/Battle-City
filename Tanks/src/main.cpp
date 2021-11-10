#include "gameplay/gameplay.h"

int main()
{
    Gameplay* gameplay = new Gameplay();

    gameplay->Run();

    delete gameplay;

    return 0;
}
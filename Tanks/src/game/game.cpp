#include "game.h"

#include <SFML/Window/Event.hpp>

#include "gameplay/gameplay.h"

using namespace sf;

namespace Battle_City 
{
    Game::Game()
    {
        exit = false;

        windowWidth = 1200;
        windowHeigth = 800;

        window.create(VideoMode(windowWidth, windowHeigth), title);
        gameplay = new Gameplay(3, false, windowWidth, windowHeigth, window);
    }

    Game::~Game()
    {
        if (gameplay != NULL) 
        {
            delete gameplay;
        }        
    }

    void Game::Run()
    {
        while (window.isOpen() && !exit)
        {
            dt = clock.restart();

            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                {
                    window.close();
                }                
            }     

            gameplay->Input();
            gameplay->Update(dt, windowWidth, windowHeigth);
            gameplay->Draw(window);

            if (gameplay->GetGameOver()) 
            {
                delete gameplay;
                gameplay = new Gameplay(3, false, windowWidth, windowHeigth, window);
            }
        }
    }
}
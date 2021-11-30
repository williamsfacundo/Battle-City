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
        sceneManager = new SceneManager();
    }

    Game::~Game()
    {
        if (gameplay != NULL) 
        {
            delete gameplay;
        }        

        delete sceneManager;
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

            switch (sceneManager->GetCurrentScene())
            {
            case Scenes::menu:



                break;
            case Scenes::credits:



                break;
            case Scenes::pvp:

                gameplay->Input();
                gameplay->Update(dt, windowWidth, windowHeigth);
                gameplay->Draw(window);

                if (gameplay->GetGameOver())
                {
                    delete gameplay;
                    gameplay = new Gameplay(4, true, windowWidth, windowHeigth, window);
                }

                break;
            case Scenes::pvscpu:

                gameplay->Input();
                gameplay->Update(dt, windowWidth, windowHeigth);
                gameplay->Draw(window);

                if (gameplay->GetGameOver())
                {
                    sceneManager->SetCurrentScene(Scenes::menu);
                }

                break;
            case Scenes::exit:

                exit = true;

                break;
            default:
                break;
            }            
        }
    }
}
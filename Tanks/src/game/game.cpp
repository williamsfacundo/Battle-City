#include "game.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "gameplay/gameplay.h"
#include "scene_manager.h"
#include "credits.h"

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
        sceneManager->SetCurrentScene(Scenes::credits);
        credits = new Credits(windowWidth, windowHeigth);
    }

    Game::~Game()
    {
        if (gameplay != NULL) 
        {
            delete gameplay;
        }        

        delete sceneManager;
        delete credits;
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

                credits->Draw(window);
                credits->Input(sceneManager);

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
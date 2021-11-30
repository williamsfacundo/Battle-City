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

        gameplay = NULL;
        sceneManager = new SceneManager();
        sceneManager->SetCurrentScene(Scenes::menu);
        credits = new Credits(windowWidth, windowHeigth);
        mainMenu = new Menu(windowWidth, windowHeigth);
    }

    Game::~Game()
    {
        if (gameplay != NULL) 
        {
            delete gameplay;
        }        

        delete sceneManager;
        delete credits;
        delete mainMenu;
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

                mainMenu->Input(sceneManager, windowWidth, windowHeigth);
                mainMenu->Update(dt);
                mainMenu->Draw(window);

                break;
            case Scenes::credits:

                credits->Draw(window);
                credits->Input(sceneManager);

                break;
            case Scenes::pvp:

                if (gameplay == NULL) 
                {
                    gameplay = new Gameplay(4, true, windowWidth, windowHeigth, window);
                }

                gameplay->Input(sceneManager);
                gameplay->Update(dt, windowWidth, windowHeigth);
                gameplay->Draw(window);

                if (gameplay->GetGameOver())
                {
                    sceneManager->SetCurrentScene(Scenes::menu);
                }

                break;
            case Scenes::pvscpu:

                if (gameplay == NULL)
                {
                    gameplay = new Gameplay(2, false, windowWidth, windowHeigth, window);
                }

                gameplay->Input(sceneManager);
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

            if (sceneManager->GetCurrentScene() != sceneManager->GetLastScene() && 
                (sceneManager->GetLastScene() == Scenes::pvp || sceneManager->GetLastScene() == Scenes::pvscpu))
            {
                delete gameplay;
                gameplay = NULL;
            }

            if (sceneManager->GetCurrentScene() != sceneManager->GetLastScene()) 
            {
                sceneManager->SetLastScene(sceneManager->GetCurrentScene());
            }
        }
    }
}
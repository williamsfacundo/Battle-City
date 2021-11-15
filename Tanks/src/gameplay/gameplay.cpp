#include "gameplay.h"

#include <SFML/Window/Event.hpp>

#include "player.h"
#include "enemy.h"
#include "collisions.h"
 
namespace Battle_City 
{
    Gameplay::Gameplay()
    {
        gameOver = false;

        windowWidth = 1200;
        windowHeigth = 800;

        window.create(VideoMode(windowWidth, windowHeigth), title);

        playerTank = new Player(window.getSize().x / 2.0f, window.getSize().y / 2.0f, { 50.0f, 50.0f }, playerTankColor);
        enemyTank = new Enemy(window.getSize().x / 3.0f, window.getSize().y / 3.0f, { 50.0f, 50.0f }, enemyTankColor);
    }

    Gameplay::~Gameplay()
    {
        delete playerTank;
        delete enemyTank;
    }

    void Gameplay::Input()
    {
        ((Player*)playerTank)->Input();
    }

    void Gameplay::Update(Time dt)
    {
        ((Player*)playerTank)->Update(dt, windowWidth, windowHeigth);
        ((Enemy*)enemyTank)->Update(dt, windowWidth, windowHeigth);

        WinCondition();
        DefeatCondition();
    }

    void Gameplay::Draw()
    {
        window.clear(Color::Black);

        playerTank->Draw(window);
        enemyTank->Draw(window);

        window.display();
    }

    void Gameplay::Run()
    {
        while (window.isOpen() && !gameOver)
        {
            dt = clock.restart();

            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            Input();
            Update(dt);
            Draw();
        }
    }

    void Gameplay::WinCondition() 
    {

    }
    
    void Gameplay::DefeatCondition()
    {
        if (enemyBulletsCollideWithPlayer()) 
        {
            gameOver = true;
        }
    }    
}
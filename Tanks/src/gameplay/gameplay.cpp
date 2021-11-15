#include "gameplay.h"

#include <SFML/Window/Event.hpp>

#include "tank.h"
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

        for (short i = 0; i < maxEnemyTanks; i++) 
        {
            enemyTank[i] = new Enemy((window.getSize().x / 15.0f) * (i+1), window.getSize().y / 3.0f, { 50.0f, 50.0f }, enemyTankColor);
        }       
    }

    Gameplay::~Gameplay()
    {
        delete playerTank;

        for (short i = 0; i < maxEnemyTanks; i++) 
        {
            if (enemyTank != NULL) 
            {
                delete enemyTank[i]; 
            }
        }        
    }

    void Gameplay::Input()
    {
        ((Player*)playerTank)->Input();
    }

    void Gameplay::Update(Time dt)
    {
        ((Player*)playerTank)->Update(dt, windowWidth, windowHeigth);

        for (short i = 0; i < maxEnemyTanks; i++) 
        {
            if (enemyTank[i] != NULL)
            { 
                ((Enemy*)enemyTank[i])->Update(dt, windowWidth, windowHeigth); 
            }
        }        

        WinCondition();
        DefeatCondition();
    }

    void Gameplay::Draw()
    {
        window.clear(Color::Black);

        playerTank->Draw(window);

        for (short i = 0; i < maxEnemyTanks; i++) 
        {
            if (enemyTank[i] != NULL)
            {
                enemyTank[i]->Draw(window);
            }
        }              

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
        if (enemiesBulletsCollideWithPlayer())
        {
            gameOver = true;
        }
    }    

    bool Gameplay::enemiesBulletsCollideWithPlayer()
    {
        bool isCollision = false;

        for (short i = 0; i < maxEnemyTanks; i++)
        {
            if (enemyTank[i] != NULL) 
            {                
                for (short j = 0; j < maxBullets; j++) 
                {
                    if (!((Tank*)enemyTank[i])->IsBulletNull(j)) 
                    {                        
                        isCollision = CollisionFunctions::CollisionRectangles(
                            ((Tank*)playerTank)->GetXPosition(), 
                            ((Tank*)playerTank)->GetYPosition(),
                            ((Tank*)playerTank)->GetSize().x, 
                            ((Tank*)playerTank)->GetSize().y,
                            ((Tank*)enemyTank[i])->GetBullet(j)->GetXPosition(), 
                            ((Tank*)enemyTank[i])->GetBullet(j)->GetYPosition(),
                            ((Bullet*)((Tank*)enemyTank[i])->GetBullet(j))->GetSize().x, 
                            ((Bullet*)((Tank*)enemyTank[i])->GetBullet(j))->GetSize().y);

                        if (isCollision) 
                        {
                            i = maxEnemyTanks;
                            j = maxBullets;
                        }
                    }                    
                }                                
            }
        }

        return isCollision;
    }
}
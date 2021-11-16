#include "gameplay.h"

#include <SFML/Window/Event.hpp>

#include "tank.h"
#include "player.h"
#include "enemy.h"
#include "collisions.h"
#include "base.h"
#include "wall.h"
 
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

        militaryBase = new Base(window.getSize().x /2.0f + 100.0f, window.getSize().y / 3.0f, {50.0f, 50.0f});

        for (short i = 0; i < maxDestroyableWalls; i++) 
        {
            destroyableWalls[i] = new Wall(window.getSize().x - (60.0f * (i + 1)), 100.0f, {50.0f, 50.0f}, true);
        }
        
        for (short i = 0; i < maxNonDestroyableWalls; i++) 
        {
            nonDestroyableWalls[i] = new Wall(window.getSize().x - (60.0f * (i + 1)), window.getSize().y - 100.0f, { 50.0f, 50.0f }, false);
        }        
    }

    Gameplay::~Gameplay()
    {
        if (playerTank != NULL)
        { 
            delete playerTank; 
        }

        if (militaryBase != NULL) 
        { 
            delete militaryBase; 
        }

        for (short i = 0; i < maxEnemyTanks; i++) 
        {
            if (enemyTank != NULL) 
            {
                delete enemyTank[i]; 
            }
        }        

        for (short i = 0; i < maxDestroyableWalls; i++)
        {
            if (destroyableWalls[i] != NULL)
            {
                delete destroyableWalls[i];
            }            
        }

        for (short i = 0; i < maxNonDestroyableWalls; i++)
        {
            if (nonDestroyableWalls[i] != NULL)
            {
                delete nonDestroyableWalls[i];
            }
        }
    }

    void Gameplay::Input()
    {
        ((Player*)playerTank)->Input();
    }

    void Gameplay::Update(Time dt)
    {
        DestroyEnemyTanksWhenHit();

        if (EnemiesBulletsCollideWithPlayer())
        {
            ((Player*)playerTank)->DecreaseLifes();
        }

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

        militaryBase->Draw(window);

        for (short i = 0; i < maxDestroyableWalls; i++)
        {
            if (destroyableWalls[i] != NULL)
            {
               destroyableWalls[i]->Draw(window);
            }
        }

        for (short i = 0; i < maxNonDestroyableWalls; i++)
        {
            if (nonDestroyableWalls[i] != NULL)
            {
                nonDestroyableWalls[i]->Draw(window);
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
        if (AllTanksDestroyed()) 
        {
            gameOver = true;
        }
    }
    
    void Gameplay::DefeatCondition()
    {
        if (((Player*)playerTank)->GetLifes() <= 0 || BulletsCollideWithMilitaryBase())
        {
            gameOver = true;
        }
    }    

    bool Gameplay::EnemiesBulletsCollideWithPlayer()
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
                            ((Tank*)enemyTank[i])->DestroyBullet(j);

                            i = maxEnemyTanks;
                            j = maxBullets;
                        }
                    }                    
                }                                
            }
        }

        return isCollision;
    }

    void Gameplay::DestroyEnemyTanksWhenHit()
    {
        for (short i = 0; i < maxEnemyTanks; i++)
        {
            if (enemyTank[i] != NULL)
            {
                for (short j = 0; j < maxBullets; j++)
                {
                    if (!((Tank*)playerTank)->IsBulletNull(j))
                    {
                        if (CollisionFunctions::CollisionRectangles(
                            ((Tank*)enemyTank[i])->GetXPosition(),
                            ((Tank*)enemyTank[i])->GetYPosition(),
                            ((Tank*)enemyTank[i])->GetSize().x,
                            ((Tank*)enemyTank[i])->GetSize().y,
                            ((Tank*)playerTank)->GetBullet(j)->GetXPosition(),
                            ((Tank*)playerTank)->GetBullet(j)->GetYPosition(),
                            ((Bullet*)((Tank*)playerTank)->GetBullet(j))->GetSize().x,
                            ((Bullet*)((Tank*)playerTank)->GetBullet(j))->GetSize().y))
                        {
                            delete enemyTank[i];
                            enemyTank[i] = NULL;

                            ((Tank*)playerTank)->DestroyBullet(j);
                        }                        
                    }
                }
            }
        }
    }

    bool Gameplay::BulletsCollideWithMilitaryBase()
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
                            ((Tank*)militaryBase)->GetXPosition(),
                            ((Tank*)militaryBase)->GetYPosition(),
                            ((Tank*)militaryBase)->GetSize().x,
                            ((Tank*)militaryBase)->GetSize().y,
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

        if (!isCollision && playerTank != NULL) 
        {
            for (short j = 0; j < maxBullets; j++)
            {
                if (!((Tank*)playerTank)->IsBulletNull(j))
                {
                    isCollision = CollisionFunctions::CollisionRectangles(
                        ((Tank*)militaryBase)->GetXPosition(),
                        ((Tank*)militaryBase)->GetYPosition(),
                        ((Tank*)militaryBase)->GetSize().x,
                        ((Tank*)militaryBase)->GetSize().y,
                        ((Tank*)playerTank)->GetBullet(j)->GetXPosition(),
                        ((Tank*)playerTank)->GetBullet(j)->GetYPosition(),
                        ((Bullet*)((Tank*)playerTank)->GetBullet(j))->GetSize().x,
                        ((Bullet*)((Tank*)playerTank)->GetBullet(j))->GetSize().y);

                    if (isCollision)
                    {                      
                        j = maxBullets;
                    }
                }
            }
        }

        return isCollision;
    }

    bool Gameplay::AllTanksDestroyed() 
    {
        bool allDestroyed = true;

        for (short i = 0; i < maxEnemyTanks; i++) 
        {
            if (enemyTank[i] != NULL) 
            {
                allDestroyed = false;

                i = maxEnemyTanks;
            }
        }

        return allDestroyed;
    }    
}
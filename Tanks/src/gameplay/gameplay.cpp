#include "gameplay.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Time.hpp>

#include "tank.h"
#include "player.h"
#include "enemy.h"
#include "collisions.h"
#include "base.h"
#include "wall.h"
 
namespace Battle_City 
{
    Gameplay::Gameplay(short numberOfPlayers)
    {
        gameOver = false;

        windowWidth = 1200;
        windowHeigth = 800;

        window.create(VideoMode(windowWidth, windowHeigth), title);
        
        for (short i = 0; i < maxPlayers; i++) 
        {
            playerTank[i] = NULL;
        }       

        if (numberOfPlayers > maxPlayers || numberOfPlayers < 1) 
        {
            numberOfPlayers = 1;
        }

        for (short i = 0; i < numberOfPlayers; i++)
        {
            switch (i)
            {
            case 0:
                playerTank[i] = new Player(window.getSize().x / 2.0f + 50 * (i + 1), window.getSize().y / 2.0f, { 50.0f, 50.0f }, playerTankColor, playerTexturesFiles, playerOneInputKeys);
                break;
            case 1:
                playerTank[i] = new Player(window.getSize().x / 2.0f + 50 * (i + 1), window.getSize().y / 2.0f, { 50.0f, 50.0f }, playerTankColor, playerTexturesFiles, playerTwoInputKeys);
                break;
            case 2:
                playerTank[i] = new Player(window.getSize().x / 2.0f + 50 * (i + 1), window.getSize().y / 2.0f, { 50.0f, 50.0f }, playerTankColor, playerTexturesFiles, playerThreeInputKeys);
                break;
            case 3:
                playerTank[i] = new Player(window.getSize().x / 2.0f + 50 * (i + 1), window.getSize().y / 2.0f, { 50.0f, 50.0f }, playerTankColor, playerTexturesFiles, playerFourInputKeys);
                break;            
            }            
        }        

        for (short i = 0; i < maxEnemyTanks; i++) 
        {
            enemyTank[i] = new Enemy((window.getSize().x / 15.0f) * (i+1) + 75, window.getSize().y / 3.0f, { 50.0f, 50.0f }, enemyTankColor, enemyTexturesFiles);
        }       

        militaryBase = new Base(window.getSize().x /2.0f + 300.0f, window.getSize().y / 2.0f, {50.0f, 50.0f});

        for (short i = 0; i < maxDestroyableWalls; i++) 
        {
            destroyableWalls[i] = new Wall(window.getSize().x / 2.0f + 55 * (i + 1), window.getSize().y / 3.0f + 350, {50.0f, 50.0f}, destroyableWallTextureFile,true);
        }
        
        for (short i = 0; i < maxNonDestroyableWalls; i++) 
        {
            nonDestroyableWalls[i] = new Wall((window.getSize().x / 15.0f) * (i + 1) + 100, window.getSize().y / 3.0f + 200, { 50.0f, 50.0f }, nonDestroyableWallTextureFile, false);
        }        
        
        mapLimitingWalls[0] = new Wall(limitingWallXOffset, limitingWallYOffset, {window.getSize().x - (limitingWallXOffset * 2.0f), limitingWallHeight}, mapLimitingWallFile, false);
        mapLimitingWalls[1] = new Wall(limitingWallXOffset, limitingWallYOffset, { limitingWallWidth, window.getSize().y - (limitingWallYOffset * 2.0f) }, mapLimitingWallFile, false);
        mapLimitingWalls[2] = new Wall(limitingWallXOffset, window.getSize().y - limitingWallYOffset, { window.getSize().x - (limitingWallXOffset * 2.0f) + limitingWallWidth, limitingWallHeight }, mapLimitingWallFile, false);
        mapLimitingWalls[3] = new Wall(window.getSize().x - limitingWallXOffset, limitingWallYOffset, { limitingWallWidth, window.getSize().y - (limitingWallYOffset * 2.0f) }, mapLimitingWallFile, false);
    }

    Gameplay::~Gameplay()
    {
        for (short i = 0; i < maxPlayers; i++) 
        {
            if (playerTank[i] != NULL)
            {
                delete playerTank[i];
                playerTank[i] = NULL;
            }
        }        

        if (militaryBase != NULL) 
        { 
            delete militaryBase;
            militaryBase = NULL;
        }

        for (short i = 0; i < maxEnemyTanks; i++) 
        {
            if (enemyTank != NULL) 
            {
                delete enemyTank[i];
                enemyTank[i] = NULL;
            }
        }        

        for (short i = 0; i < maxDestroyableWalls; i++)
        {
            if (destroyableWalls[i] != NULL)
            {
                delete destroyableWalls[i];
                destroyableWalls[i] = NULL;
            }            
        }

        for (short i = 0; i < maxNonDestroyableWalls; i++)
        {
            if (nonDestroyableWalls[i] != NULL) 
            {
                delete nonDestroyableWalls[i];
                nonDestroyableWalls[i] = NULL;
            }            
        }

        for (short i = 0; i < maxMapLimitingWalls; i++) 
        {
            if (mapLimitingWalls[i] != NULL)
            {        
                delete mapLimitingWalls[i];
                mapLimitingWalls[i] = NULL;
            }            
        }
    }

    void Gameplay::Input()
    {
        for (short i = 0; i < maxPlayers; i++) 
        {
            if (playerTank[i] != NULL)
            {
                ((Player*)playerTank[i])->Input();
            }
        }        
    }

    void Gameplay::Update(Time dt)
    {
        for (short i = 0; i < maxPlayers; i++)
        {
            if (playerTank[i] != NULL)
            {
                ((Player*)playerTank[i])->Update(dt, windowWidth, windowHeigth);
            }
        }        

        for (short i = 0; i < maxEnemyTanks; i++) 
        {
            if (enemyTank[i] != NULL)
            { 
                ((Enemy*)enemyTank[i])->Update(dt, windowWidth, windowHeigth); 
            }
        }    

        DestroyEnemyTanksWhenHit();
        DestroyDestroyableWallsWhenHit();
        DestroyDestroyableWallsWhenHit();
        DestroyBulletsWhenHitNonDestroyableWalls();
        TanksCollideWithWalls();
        TanksCollideWithMilitaryBase();
        EnemiesBulletsCollideWithPlayers();
        TanksCollideWithEachOther();

        WinCondition();
        DefeatCondition();
    }

    void Gameplay::Draw()
    {
        window.clear(Color::Black);

        for (short i = 0; i < maxPlayers; i++)
        {
            if (playerTank[i] != NULL)
            {
                ((Player*)playerTank[i])->Draw(window);
            }
        }        

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

        for (short i = 0; i < maxMapLimitingWalls; i++)
        {
            if (mapLimitingWalls[i] != NULL)
            {
                mapLimitingWalls[i]->Draw(window);
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
                {
                    window.close();
                }
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
        bool allPlayerTanksDestroyed = true;

        for (short i = 0; i < maxPlayers; i++) 
        {
            if (playerTank[i] != NULL)
            {
                allPlayerTanksDestroyed = false;
                i = maxPlayers;
            }
        }

        if (allPlayerTanksDestroyed || BulletsCollideWithMilitaryBase())
        {
            gameOver = true;
        }               
    }    

    void Gameplay::EnemiesBulletsCollideWithPlayers()
    {
        for (short i = 0; i < maxEnemyTanks; i++)
        {
            if (enemyTank[i] != NULL) 
            {                
                for (short j = 0; j < maxBullets; j++) 
                {
                    if (!((Tank*)enemyTank[i])->IsBulletNull(j)) 
                    {                        
                        for (short k = 0; k < maxPlayers; k++) 
                        {
                            if (playerTank[k] != NULL)
                            {
                                if (CollisionFunctions::CollisionRectangles(
                                    ((Tank*)playerTank[k])->GetXPosition(),
                                    ((Tank*)playerTank[k])->GetYPosition(),
                                    ((Tank*)playerTank[k])->GetSize().x,
                                    ((Tank*)playerTank[k])->GetSize().y,
                                    ((Tank*)enemyTank[i])->GetBullet(j)->GetXPosition(),
                                    ((Tank*)enemyTank[i])->GetBullet(j)->GetYPosition(),
                                    ((Bullet*)((Tank*)enemyTank[i])->GetBullet(j))->GetSize().x,
                                    ((Bullet*)((Tank*)enemyTank[i])->GetBullet(j))->GetSize().y))
                                {
                                    ((Player*)playerTank[k])->DecreaseLifes();
                                    ((Tank*)enemyTank[i])->DestroyBullet(j);
                                    
                                    DestroyPlayerTankIfHasNoLifesLeft(k);
                                    
                                    k = maxPlayers;
                                }
                            }                            
                        }                       
                    }                    
                }                                
            }
        }        
    }

    void Gameplay::DestroyEnemyTanksWhenHit()
    {
        for (short i = 0; i < maxPlayers; i++)
        {
            if (playerTank[i] != NULL)
            {
                for (short j = 0; j < maxBullets; j++)
                {
                    if (!((Tank*)playerTank[i])->IsBulletNull(j))
                    {
                        for (short k = 0; k < maxEnemyTanks; k++)
                        {
                            if (enemyTank[k] != NULL)
                            {
                                if (CollisionFunctions::CollisionRectangles(
                                    ((Tank*)enemyTank[k])->GetXPosition(),
                                    ((Tank*)enemyTank[k])->GetYPosition(),
                                    ((Tank*)enemyTank[k])->GetSize().x,
                                    ((Tank*)enemyTank[k])->GetSize().y,
                                    ((Tank*)playerTank[i])->GetBullet(j)->GetXPosition(),
                                    ((Tank*)playerTank[i])->GetBullet(j)->GetYPosition(),
                                    ((Bullet*)((Tank*)playerTank[i])->GetBullet(j))->GetSize().x,
                                    ((Bullet*)((Tank*)playerTank[i])->GetBullet(j))->GetSize().y))
                                {                                    
                                    ((Tank*)playerTank[i])->DestroyBullet(j);                                    

                                    delete enemyTank[k];
                                    enemyTank[k] = NULL;

                                    k = maxEnemyTanks;
                                }
                            }
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

        if (!isCollision) 
        {
            for (short i = 0; i < maxPlayers; i++) 
            {
                if (playerTank[i] != NULL)
                {
                    for (short j = 0; j < maxBullets; j++)
                    {
                        if (!((Tank*)playerTank[i])->IsBulletNull(j))
                        {
                            isCollision = CollisionFunctions::CollisionRectangles(
                                ((Tank*)militaryBase)->GetXPosition(),
                                ((Tank*)militaryBase)->GetYPosition(),
                                ((Tank*)militaryBase)->GetSize().x,
                                ((Tank*)militaryBase)->GetSize().y,
                                ((Tank*)playerTank[i])->GetBullet(j)->GetXPosition(),
                                ((Tank*)playerTank[i])->GetBullet(j)->GetYPosition(),
                                ((Bullet*)((Tank*)playerTank[i])->GetBullet(j))->GetSize().x,
                                ((Bullet*)((Tank*)playerTank[i])->GetBullet(j))->GetSize().y);

                            if (isCollision)
                            {
                                j = maxBullets;
                                i = maxPlayers;
                            }
                        }
                    }
                }
            }            
        }

        return isCollision;
    }

    void Gameplay::DestroyDestroyableWallsWhenHit()
    {
        for (short i = 0; i < maxEnemyTanks; i++)
        {
            if (enemyTank[i] != NULL)
            {
                for (short j = 0; j < maxBullets; j++)
                {
                    if (!((Tank*)enemyTank[i])->IsBulletNull(j))
                    {
                        for (short k = 0; k < maxDestroyableWalls; k++) 
                        {
                            if (destroyableWalls[k] != NULL)
                            {
                                if (CollisionFunctions::CollisionRectangles(
                                    ((Wall*)destroyableWalls[k])->GetXPosition(),
                                    ((Wall*)destroyableWalls[k])->GetYPosition(),
                                    ((Wall*)destroyableWalls[k])->GetSize().x,
                                    ((Wall*)destroyableWalls[k])->GetSize().y,
                                    ((Tank*)enemyTank[i])->GetBullet(j)->GetXPosition(),
                                    ((Tank*)enemyTank[i])->GetBullet(j)->GetYPosition(),
                                    ((Bullet*)((Tank*)enemyTank[i])->GetBullet(j))->GetSize().x,
                                    ((Bullet*)((Tank*)enemyTank[i])->GetBullet(j))->GetSize().y)) 
                                {
                                    ((Tank*)enemyTank[i])->DestroyBullet(j);

                                    delete destroyableWalls[k];
                                    destroyableWalls[k] = NULL;

                                    k = maxDestroyableWalls;
                                }
                            }
                        }
                                                
                    }
                }
            }
        }

        for (short i = 0; i < maxPlayers; i++) 
        {
            if (playerTank[i] != NULL)
            {
                for (short j = 0; j < maxBullets; j++)
                {
                    if (!((Tank*)playerTank[i])->IsBulletNull(j))
                    {
                        for (short k = 0; k < maxDestroyableWalls; k++)
                        {
                            if (destroyableWalls[k] != NULL)
                            {
                                if (CollisionFunctions::CollisionRectangles(
                                    ((Wall*)destroyableWalls[k])->GetXPosition(),
                                    ((Wall*)destroyableWalls[k])->GetYPosition(),
                                    ((Wall*)destroyableWalls[k])->GetSize().x,
                                    ((Wall*)destroyableWalls[k])->GetSize().y,
                                    ((Tank*)playerTank[i])->GetBullet(j)->GetXPosition(),
                                    ((Tank*)playerTank[i])->GetBullet(j)->GetYPosition(),
                                    ((Bullet*)((Tank*)playerTank[i])->GetBullet(j))->GetSize().x,
                                    ((Bullet*)((Tank*)playerTank[i])->GetBullet(j))->GetSize().y))
                                {
                                    ((Tank*)playerTank[i])->DestroyBullet(j);

                                    delete destroyableWalls[k];
                                    destroyableWalls[k] = NULL;

                                    k = maxDestroyableWalls;
                                }
                            }
                        }
                    }
                }
            }            
        }                
    }

    void Gameplay::DestroyBulletsWhenHitNonDestroyableWalls() 
    {
        for (short i = 0; i < maxEnemyTanks; i++)
        {
            if (enemyTank[i] != NULL)
            {
                for (short j = 0; j < maxBullets; j++)
                {
                    if (!((Tank*)enemyTank[i])->IsBulletNull(j))
                    {
                        for (short k = 0; k < maxNonDestroyableWalls; k++)
                        {
                            if (nonDestroyableWalls[k] != NULL)
                            {
                                if (CollisionFunctions::CollisionRectangles(
                                    ((Wall*)nonDestroyableWalls[k])->GetXPosition(),
                                    ((Wall*)nonDestroyableWalls[k])->GetYPosition(),
                                    ((Wall*)nonDestroyableWalls[k])->GetSize().x,
                                    ((Wall*)nonDestroyableWalls[k])->GetSize().y,
                                    ((Tank*)enemyTank[i])->GetBullet(j)->GetXPosition(),
                                    ((Tank*)enemyTank[i])->GetBullet(j)->GetYPosition(),
                                    ((Bullet*)((Tank*)enemyTank[i])->GetBullet(j))->GetSize().x,
                                    ((Bullet*)((Tank*)enemyTank[i])->GetBullet(j))->GetSize().y))
                                {
                                    ((Tank*)enemyTank[i])->DestroyBullet(j);                                    

                                    k = maxNonDestroyableWalls;
                                }
                            }
                        }
                    }

                    if (!((Tank*)enemyTank[i])->IsBulletNull(j)) 
                    {
                        for (short k = 0; k < maxMapLimitingWalls; k++)
                        {
                            if (mapLimitingWalls[k] != NULL)
                            {
                                if (CollisionFunctions::CollisionRectangles(
                                    ((Wall*)mapLimitingWalls[k])->GetXPosition(),
                                    ((Wall*)mapLimitingWalls[k])->GetYPosition(),
                                    ((Wall*)mapLimitingWalls[k])->GetSize().x,
                                    ((Wall*)mapLimitingWalls[k])->GetSize().y,
                                    ((Tank*)enemyTank[i])->GetBullet(j)->GetXPosition(),
                                    ((Tank*)enemyTank[i])->GetBullet(j)->GetYPosition(),
                                    ((Bullet*)((Tank*)enemyTank[i])->GetBullet(j))->GetSize().x,
                                    ((Bullet*)((Tank*)enemyTank[i])->GetBullet(j))->GetSize().y))
                                {
                                    ((Tank*)enemyTank[i])->DestroyBullet(j);

                                    k = maxMapLimitingWalls;
                                }
                            }
                        }
                    }
                }
            }
        }        

        for (short i = 0; i < maxPlayers; i++)
        {
            if (playerTank[i] != NULL)
            {
                for (short j = 0; j < maxBullets; j++)
                {
                    if (!((Tank*)playerTank[i])->IsBulletNull(j))
                    {
                        for (short k = 0; k < maxNonDestroyableWalls; k++)
                        {
                            if (nonDestroyableWalls[k] != NULL)
                            {
                                if (CollisionFunctions::CollisionRectangles(
                                    ((Wall*)nonDestroyableWalls[k])->GetXPosition(),
                                    ((Wall*)nonDestroyableWalls[k])->GetYPosition(),
                                    ((Wall*)nonDestroyableWalls[k])->GetSize().x,
                                    ((Wall*)nonDestroyableWalls[k])->GetSize().y,
                                    ((Tank*)playerTank[i])->GetBullet(j)->GetXPosition(),
                                    ((Tank*)playerTank[i])->GetBullet(j)->GetYPosition(),
                                    ((Bullet*)((Tank*)playerTank[i])->GetBullet(j))->GetSize().x,
                                    ((Bullet*)((Tank*)playerTank[i])->GetBullet(j))->GetSize().y))
                                {
                                    ((Tank*)playerTank[i])->DestroyBullet(j);

                                    k = maxNonDestroyableWalls;
                                }
                            }
                        }
                    }

                    if (!((Tank*)playerTank[i])->IsBulletNull(j))
                    {
                        for (short k = 0; k < maxMapLimitingWalls; k++)
                        {
                            if (mapLimitingWalls[k] != NULL)
                            {
                                if (CollisionFunctions::CollisionRectangles(
                                    ((Wall*)mapLimitingWalls[k])->GetXPosition(),
                                    ((Wall*)mapLimitingWalls[k])->GetYPosition(),
                                    ((Wall*)mapLimitingWalls[k])->GetSize().x,
                                    ((Wall*)mapLimitingWalls[k])->GetSize().y,
                                    ((Tank*)playerTank[i])->GetBullet(j)->GetXPosition(),
                                    ((Tank*)playerTank[i])->GetBullet(j)->GetYPosition(),
                                    ((Bullet*)((Tank*)playerTank[i])->GetBullet(j))->GetSize().x,
                                    ((Bullet*)((Tank*)playerTank[i])->GetBullet(j))->GetSize().y))
                                {
                                    ((Tank*)playerTank[i])->DestroyBullet(j);

                                    k = maxMapLimitingWalls;
                                }
                            }
                        }
                    }
                }
            }
        }        
    }    

    void Gameplay::TanksCollideWithWalls() 
    {
        for (short i = 0; i < maxEnemyTanks; i++) 
        {
            if (enemyTank[i] != NULL) 
            {
                for (short j = 0; j < maxDestroyableWalls; j++)
                {
                    if (destroyableWalls[j] != NULL) 
                    {
                        CollisionFunctions::CollisionTankWithStaticRectangleObject((Tank*)enemyTank[i],
                            { ((Wall*)destroyableWalls[j])->GetXPosition(), ((Wall*)destroyableWalls[j])->GetYPosition()}, 
                            ((Wall*)destroyableWalls[j])->GetSize());
                    }
                    
                }

                for (short j = 0; j < maxNonDestroyableWalls; j++)
                {
                    if (nonDestroyableWalls[j] != NULL)
                    {
                        CollisionFunctions::CollisionTankWithStaticRectangleObject((Tank*)enemyTank[i],
                            { ((Wall*)nonDestroyableWalls[j])->GetXPosition(), ((Wall*)nonDestroyableWalls[j])->GetYPosition() },
                            ((Wall*)nonDestroyableWalls[j])->GetSize());
                    }
                }

                for (short j = 0; j < maxMapLimitingWalls; j++) 
                {
                    if (mapLimitingWalls[j] != NULL) 
                    {
                        CollisionFunctions::CollisionTankWithStaticRectangleObject((Tank*)enemyTank[i],
                            { ((Wall*)mapLimitingWalls[j])->GetXPosition(), ((Wall*)mapLimitingWalls[j])->GetYPosition() },
                            ((Wall*)mapLimitingWalls[j])->GetSize());
                    }
                }
            }            
        }       

        for (short i = 0; i < maxPlayers; i++) 
        {
            if (playerTank[i] != NULL)
            {
                for (short j = 0; j < maxDestroyableWalls; j++)
                {
                    if (destroyableWalls[j] != NULL)
                    {
                        CollisionFunctions::CollisionTankWithStaticRectangleObject((Tank*)playerTank[i],
                            { ((Wall*)destroyableWalls[j])->GetXPosition(), ((Wall*)destroyableWalls[j])->GetYPosition() },
                            ((Wall*)destroyableWalls[j])->GetSize());
                    }

                }
            }
        }        

        for (short i = 0; i < maxPlayers; i++)
        {
            if (playerTank[i] != NULL)
            {
                for (short j = 0; j < maxNonDestroyableWalls; j++)
                {
                    if (nonDestroyableWalls[j] != NULL)
                    {
                        CollisionFunctions::CollisionTankWithStaticRectangleObject((Tank*)playerTank[i],
                            { ((Wall*)nonDestroyableWalls[j])->GetXPosition(), ((Wall*)nonDestroyableWalls[j])->GetYPosition() },
                            ((Wall*)nonDestroyableWalls[j])->GetSize());
                    }
                }
            }
        }        

        for (short i = 0; i < maxPlayers; i++)
        {
            if (playerTank[i] != NULL)
            {
                for (short j = 0; j < maxMapLimitingWalls; j++)
                {
                    if (mapLimitingWalls[j] != NULL)
                    {
                        CollisionFunctions::CollisionTankWithStaticRectangleObject((Tank*)playerTank[i],
                            { ((Wall*)mapLimitingWalls[j])->GetXPosition(), ((Wall*)mapLimitingWalls[j])->GetYPosition() },
                            ((Wall*)mapLimitingWalls[j])->GetSize());
                    }
                }
            }
        }       
    }

    void Gameplay::TanksCollideWithMilitaryBase() 
    {
        for (short i = 0; i < maxEnemyTanks; i++) 
        {
            if (enemyTank[i] != NULL && militaryBase != NULL) 
            {
                CollisionFunctions::CollisionTankWithStaticRectangleObject((Tank*)enemyTank[i], { ((Base*)militaryBase)->GetXPosition(),
                    ((Base*)militaryBase)->GetYPosition() }, ((Base*)militaryBase)->GetSize());
            }
        }

        for (short i = 0; i < maxPlayers; i++)
        {
            if (playerTank[i] != NULL && militaryBase != NULL)
            {
                CollisionFunctions::CollisionTankWithStaticRectangleObject((Tank*)playerTank[i], { ((Base*)militaryBase)->GetXPosition(),
                    ((Base*)militaryBase)->GetYPosition() }, ((Base*)militaryBase)->GetSize());
            }
        }        
    }

    void Gameplay::TanksCollideWithEachOther() 
    {
        for (short i = 0; i < maxPlayers; i++)
        {
            if (playerTank[i] != NULL) 
            {
                for (short j = 0; j < maxEnemyTanks; j++)
                {
                    if (enemyTank[j] != NULL)
                    {
                        CollisionFunctions::TanksCollision((Tank*)playerTank[i], (Tank*)enemyTank[j]);
                    }
                }
            }            
        }        
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

    void Gameplay::DestroyPlayerTankIfHasNoLifesLeft(short index)
    {
        if (((Player*)playerTank[index])->GetLifes() <= 0) 
        {
            delete playerTank[index];
            playerTank[index] = NULL;
        }
    }
}
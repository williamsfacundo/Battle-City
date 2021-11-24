#include "gameplay.h"

#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Time.hpp>

#include "tank.h"
#include "player.h"
#include "enemy.h"
#include "collisions.h"
#include "base.h"
#include "wall.h"

#include "global_vars.h"
 
namespace Battle_City 
{
    Gameplay::Gameplay(short numberOfPlayers)
    {
        gameOver = false;

        windowWidth = 1200;
        windowHeigth = 800;

        Vector2f UIkeysSeparation = {4.5f, 4.5f};
        Vector2f playerInputUIPositions[maxKeys] = { 
          {windowWidth - (UISpriteSize.x * 2) - (UIkeysSeparation.x * 2), limitingWallYOffset + (UIkeysSeparation.y * 8) + (UISpriteSize.y * 7)},
          {windowWidth - UISpriteSize.x - UIkeysSeparation.x, limitingWallYOffset + (UIkeysSeparation.y * 8) + (UISpriteSize.y * 7)},
          {windowWidth - (UISpriteSize.x * 1.5f) - UIkeysSeparation.x, limitingWallYOffset + (UIkeysSeparation.y * 3) + (UISpriteSize.y * 2)},
          {UIkeysSeparation.x, limitingWallYOffset + (UIkeysSeparation.y * 2) + UISpriteSize.y},
          {(UISpriteSize.x * 0.5f) + UIkeysSeparation.x, limitingWallYOffset + (UIkeysSeparation.y * 3) + (UISpriteSize.y * 2)},
          {UISpriteSize.x + (UIkeysSeparation.x * 2), limitingWallYOffset + (UIkeysSeparation.y * 2) + UISpriteSize.y},
          {(UISpriteSize.x * 0.5f) + UIkeysSeparation.x, limitingWallYOffset + (UIkeysSeparation.y * 7) + (UISpriteSize.y * 6)},
          {UIkeysSeparation.x, limitingWallYOffset + (UIkeysSeparation.y * 8) + (UISpriteSize.y * 7)},
          {(UISpriteSize.x * 0.5f) + UIkeysSeparation.x, limitingWallYOffset + (UIkeysSeparation.y * 9) + (UISpriteSize.y * 8)},
          {UISpriteSize.x + (UIkeysSeparation.x * 2), limitingWallYOffset + (UIkeysSeparation.y * 8) + (UISpriteSize.y * 7)},
          {windowWidth - (UISpriteSize.x * 1.5f) - UIkeysSeparation.x, limitingWallYOffset + (UIkeysSeparation.y * 11) + (UISpriteSize.y * 10)},
          {windowWidth - (UISpriteSize.x * 2) - (UIkeysSeparation.x * 2), limitingWallYOffset + (UIkeysSeparation.y * 2) + UISpriteSize.y},
          {(UISpriteSize.x * 0.5f) + UIkeysSeparation.x, limitingWallYOffset + (UIkeysSeparation.y * 11) + (UISpriteSize.y * 10)},
          {windowWidth - (UISpriteSize.x * 1.5f) - UIkeysSeparation.x, limitingWallYOffset + (UIkeysSeparation.y * 5) + (UISpriteSize.y * 4)},
          {windowWidth - UISpriteSize.x - UIkeysSeparation.x, limitingWallYOffset + (UIkeysSeparation.y * 2) + UISpriteSize.y},
          {windowWidth - (UISpriteSize.x * 1.5f) - UIkeysSeparation.x, limitingWallYOffset + (UIkeysSeparation.y * 9) + (UISpriteSize.y * 8)},
          {(UISpriteSize.x * 0.5f) + UIkeysSeparation.x, limitingWallYOffset + (UIkeysSeparation.y * 5) + (UISpriteSize.y * 4)},
          {(UISpriteSize.x * 0.5f) + UIkeysSeparation.x, limitingWallYOffset + UIkeysSeparation.y},
          {windowWidth - (UISpriteSize.x * 1.5f) - UIkeysSeparation.x, limitingWallYOffset + UIkeysSeparation.y},
          {windowWidth - (UISpriteSize.x * 1.5f) - UIkeysSeparation.x, limitingWallYOffset + (UIkeysSeparation.y * 7) + (UISpriteSize.y * 6)}};

        this->numberOfPlayers = numberOfPlayers;

        window.create(VideoMode(windowWidth, windowHeigth), title);
        
        for (short i = 0; i < maxKeys; i++) 
        { 
            inputKeysUITextures[i].loadFromFile(keysUIFiles[i]);            
        }

        Vector2f actualSize;

        for (short i = 0; i < maxKeys; i++) 
        {
            inputKeysUISprites[i].setTexture(inputKeysUITextures[i]);           

            actualSize.x = static_cast<float>(inputKeysUISprites[i].getTextureRect().width);
            actualSize.y = static_cast<float>(inputKeysUISprites[i].getTextureRect().height);

            inputKeysUISprites[i].setScale(UISpriteSize.x / actualSize.x, UISpriteSize.y / actualSize.y);
            inputKeysUISprites[i].setPosition(playerInputUIPositions[i].x, playerInputUIPositions[i].y);
        }        

        for (short i = 0; i < maxHearts; i++) 
        {
            heartsTextures[i].loadFromFile(heartsFiles[i]);
        }        
        
        for (short i = 0; i < maxHearts; i++)
        {
            heartsSprites[i].setTexture(heartsTextures[i]);

            actualSize.x = static_cast<float>(heartsSprites[i].getTextureRect().width);
            actualSize.y = static_cast<float>(heartsSprites[i].getTextureRect().height);

            heartsSprites[i].setScale(heartsSpriteSize.x / actualSize.x, heartsSpriteSize.y / actualSize.y);
        }        

        textFont.loadFromFile(textFontFile);
        
        enemiesLeftMeassegeText.setString("ENEMIES LEFT");
        enemiesLeftMeassegeText.setCharacterSize(24);
        enemiesLeftMeassegeText.setFillColor(Color::White);
        enemiesLeftMeassegeText.setFont(textFont);
        enemiesLeftMeassegeText.setPosition(windowWidth / 2.0f - (24 * 7), windowHeigth - (limitingWallXOffset / 3));
        
        enemiesLeftText.setCharacterSize(24);
        enemiesLeftText.setFillColor(Color::Red);
        enemiesLeftText.setFont(textFont);
        enemiesLeftText.setPosition(static_cast<float>(windowWidth / 2.0f + (24 * 5.5)), static_cast<float>(windowHeigth - (limitingWallXOffset / 3)));


        for (short i = 0; i < maxPlayers; i++) 
        {
            playerTanks[i] = NULL;
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
                playerTanks[i] = new Player(window.getSize().x / 2.0f + 50 * (i + 1), window.getSize().y / 2.0f, { 40.0f, 40.0f }, playerTankColor, playerOneTexturesFiles, playerOneInputKeys);
                break;
            case 1:
                playerTanks[i] = new Player(window.getSize().x / 2.0f + 50 * (i + 1), window.getSize().y / 2.0f, { 40.0f, 40.0f }, playerTankColor, playerTwoTexturesFiles, playerTwoInputKeys);
                break;
            case 2:
                playerTanks[i] = new Player(window.getSize().x / 2.0f + 50 * (i + 1), window.getSize().y / 2.0f, { 40.0f, 40.0f }, playerTankColor, playerThreeTexturesFiles, playerThreeInputKeys);
                break;
            case 3:
                playerTanks[i] = new Player(window.getSize().x / 2.0f + 50 * (i + 1), window.getSize().y / 2.0f, { 40.0f, 40.0f }, playerTankColor, playerFourTexturesFiles, playerFourInputKeys);
                break;            
            }            
        }        

        for (short i = 0; i < maxEnemyTanks; i++) 
        {
            enemyTanks[i] = new Enemy((window.getSize().x / 15.0f) * (i+1) + 125, window.getSize().y / 3.0f, { 40.0f, 40.0f }, enemyTankColor, enemyTexturesFiles);
        }       

        militaryBase = new Base(window.getSize().x /2.0f + 300.0f, window.getSize().y / 2.0f, {45.0f, 45.0f});

        for (short i = 0; i < maxDestroyableWallRows; i++) 
        {
            for (short j = 0; j < maxDestroyableWallColumns; j++)
            {
                destroyableWalls[i][j] = new Wall(window.getSize().x / 2.0f + 20 * i, window.getSize().y / 3.0f + 350 + 20 * j, { 20.0f, 20.0f }, destroyableWallTextureFile, true);
            }            
        }
        
        for (short i = 0; i < maxNonDestroyableWalls; i++) 
        {
            nonDestroyableWalls[i] = new Wall((window.getSize().x / 12.0f) * (i + 1) + 100, window.getSize().y / 3.0f + 200, { 45.0f, 45.0f }, nonDestroyableWallTextureFile, false);
        }        
        
        mapLimitingWalls[0] = new Wall(limitingWallXOffset, limitingWallYOffset, {window.getSize().x - (limitingWallXOffset * 2.0f), limitingWallHeight}, mapLimitingWallFile, false);
        mapLimitingWalls[1] = new Wall(limitingWallXOffset, limitingWallYOffset, { limitingWallWidth, window.getSize().y - (limitingWallYOffset * 2.0f) }, mapLimitingWallFile, false);
        mapLimitingWalls[2] = new Wall(limitingWallXOffset, window.getSize().y - limitingWallYOffset, { window.getSize().x - (limitingWallXOffset * 2.0f), limitingWallHeight }, mapLimitingWallFile, false);
        mapLimitingWalls[3] = new Wall(window.getSize().x - limitingWallXOffset - limitingWallWidth, limitingWallYOffset, { limitingWallWidth, window.getSize().y - (limitingWallYOffset * 2.0f) }, mapLimitingWallFile, false);
    }

    Gameplay::~Gameplay()
    {
        for (short i = 0; i < maxPlayers; i++) 
        {
            if (playerTanks[i] != NULL)
            {
                delete playerTanks[i];
                playerTanks[i] = NULL;
            }
        }        

        if (militaryBase != NULL) 
        { 
            delete militaryBase;
            militaryBase = NULL;
        }

        for (short i = 0; i < maxEnemyTanks; i++) 
        {
            if (enemyTanks != NULL) 
            {
                delete enemyTanks[i];
                enemyTanks[i] = NULL;
            }
        }        

        for (short i = 0; i < maxDestroyableWallRows; i++)
        {
            for (short j = 0; j < maxDestroyableWallColumns; j++) 
            {
                if (destroyableWalls[i] != NULL)
                {
                    delete destroyableWalls[i][j];
                    destroyableWalls[i][j] = NULL;
                }
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
            if (playerTanks[i] != NULL)
            {
                playerTanks[i]->Input();
            }
        }        
    }

    void Gameplay::Update(Time dt)
    {
        short enemies = 0;

        for (short i = 0; i < maxEnemyTanks; i++) 
        {
            if (enemyTanks[i] != NULL) 
            {
                enemies += 1;
            }
        }

        enemiesLeftText.setString(to_string(enemies));

        for (short i = 0; i < maxPlayers; i++)
        {
            if (playerTanks[i] != NULL)
            {
                playerTanks[i]->Update(dt, windowWidth, windowHeigth);
            }
        }        

        for (short i = 0; i < maxEnemyTanks; i++) 
        {
            if (enemyTanks[i] != NULL)
            { 
                enemyTanks[i]->Update(dt, windowWidth, windowHeigth);
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
            if (playerTanks[i] != NULL)
            {
                playerTanks[i]->Draw(window);
            }
        }        

        for (short i = 0; i < maxEnemyTanks; i++) 
        {
            if (enemyTanks[i] != NULL)
            {
                enemyTanks[i]->Draw(window);
            }
        }

        militaryBase->Draw(window);

        for (short i = 0; i < maxDestroyableWallRows; i++)
        {
            for (short j = 0; j < maxDestroyableWallRows; j++)
            { 
                if (destroyableWalls[i][j] != NULL)
                {
                    destroyableWalls[i][j]->Draw(window);
                }
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

        DrawTanksMoveKeysUI();
        DrawHearts();
        window.draw(enemiesLeftMeassegeText);
        window.draw(enemiesLeftText);

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
            if (playerTanks[i] != NULL)
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
            if (enemyTanks[i] != NULL) 
            {                
                for (short j = 0; j < maxBullets; j++) 
                {
                    if (!enemyTanks[i]->IsBulletNull(j)) 
                    {                        
                        for (short k = 0; k < maxPlayers; k++) 
                        {
                            if (playerTanks[k] != NULL)
                            {
                                if (CollisionFunctions::CollisionRectangles(
                                    playerTanks[k]->GetXPosition(),
                                    playerTanks[k]->GetYPosition(),
                                    playerTanks[k]->GetSize().x,
                                    playerTanks[k]->GetSize().y,
                                    enemyTanks[i]->GetBullet(j)->GetXPosition(),
                                    enemyTanks[i]->GetBullet(j)->GetYPosition(),
                                    enemyTanks[i]->GetBullet(j)->GetSize().x,
                                    enemyTanks[i]->GetBullet(j)->GetSize().y))
                                {
                                    playerTanks[k]->DecreaseLifes();
                                    enemyTanks[i]->DestroyBullet(j);
                                    
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
            if (playerTanks[i] != NULL)
            {
                for (short j = 0; j < maxBullets; j++)
                {
                    if (!playerTanks[i]->IsBulletNull(j))
                    {
                        for (short k = 0; k < maxEnemyTanks; k++)
                        {
                            if (enemyTanks[k] != NULL)
                            {
                                if (CollisionFunctions::CollisionRectangles(
                                    enemyTanks[k]->GetXPosition(),
                                    enemyTanks[k]->GetYPosition(),
                                    enemyTanks[k]->GetSize().x,
                                    enemyTanks[k]->GetSize().y,
                                    playerTanks[i]->GetBullet(j)->GetXPosition(),
                                    playerTanks[i]->GetBullet(j)->GetYPosition(),
                                    playerTanks[i]->GetBullet(j)->GetSize().x,
                                    playerTanks[i]->GetBullet(j)->GetSize().y))
                                {                                    
                                    playerTanks[i]->DestroyBullet(j);                                    

                                    delete enemyTanks[k];
                                    enemyTanks[k] = NULL;

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
            if (enemyTanks[i] != NULL)
            {
                for (short j = 0; j < maxBullets; j++)
                {
                    if (!enemyTanks[i]->IsBulletNull(j))
                    {
                        isCollision = CollisionFunctions::CollisionRectangles(
                            militaryBase->GetXPosition(),
                            militaryBase->GetYPosition(),
                            militaryBase->GetSize().x,
                            militaryBase->GetSize().y,
                            enemyTanks[i]->GetBullet(j)->GetXPosition(),
                            enemyTanks[i]->GetBullet(j)->GetYPosition(),
                            enemyTanks[i]->GetBullet(j)->GetSize().x,
                            enemyTanks[i]->GetBullet(j)->GetSize().y);

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
                if (playerTanks[i] != NULL)
                {
                    for (short j = 0; j < maxBullets; j++)
                    {
                        if (!playerTanks[i]->IsBulletNull(j))
                        {
                            isCollision = CollisionFunctions::CollisionRectangles(
                                militaryBase->GetXPosition(),
                                militaryBase->GetYPosition(),
                                militaryBase->GetSize().x,
                                militaryBase->GetSize().y,
                                playerTanks[i]->GetBullet(j)->GetXPosition(),
                                playerTanks[i]->GetBullet(j)->GetYPosition(),
                                playerTanks[i]->GetBullet(j)->GetSize().x,
                                playerTanks[i]->GetBullet(j)->GetSize().y);

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
            if (enemyTanks[i] != NULL)
            {
                for (short j = 0; j < maxBullets; j++)
                {
                    if (!enemyTanks[i]->IsBulletNull(j))
                    {
                        for (short k = 0; k < maxDestroyableWallRows; k++) 
                        {
                            for (short h = 0; h < maxDestroyableWallColumns; h++) 
                            {
                                if (destroyableWalls[k][j] != NULL)
                                {
                                    if (CollisionFunctions::CollisionRectangles(
                                        destroyableWalls[k][j]->GetXPosition(),
                                        destroyableWalls[k][j]->GetYPosition(),
                                        destroyableWalls[k][j]->GetSize().x,
                                        destroyableWalls[k][j]->GetSize().y,
                                        enemyTanks[i]->GetBullet(j)->GetXPosition(),
                                        enemyTanks[i]->GetBullet(j)->GetYPosition(),
                                        enemyTanks[i]->GetBullet(j)->GetSize().x,
                                        enemyTanks[i]->GetBullet(j)->GetSize().y))
                                    {
                                        enemyTanks[i]->DestroyBullet(j);

                                        delete destroyableWalls[k][j];
                                        destroyableWalls[k][j] = NULL;
                                                                                
                                        k = maxDestroyableWallRows;
                                        h = maxDestroyableWallColumns;
                                    }
                                }
                            }                            
                        }                                                
                    }
                }
            }
        }

        for (short i = 0; i < maxPlayers; i++) 
        {
            if (playerTanks[i] != NULL)
            {
                for (short j = 0; j < maxBullets; j++)
                {
                    if (!playerTanks[i]->IsBulletNull(j))
                    {
                        for (short k = 0; k < maxDestroyableWallRows; k++)
                        {
                            for (short h = 0; h < maxDestroyableWallColumns; h++) 
                            {
                                if (destroyableWalls[k][j] != NULL)
                                {
                                    if (CollisionFunctions::CollisionRectangles(
                                        destroyableWalls[k][j]->GetXPosition(),
                                        destroyableWalls[k][j]->GetYPosition(),
                                        destroyableWalls[k][j]->GetSize().x,
                                        destroyableWalls[k][j]->GetSize().y,
                                        playerTanks[i]->GetBullet(j)->GetXPosition(),
                                        playerTanks[i]->GetBullet(j)->GetYPosition(),
                                        playerTanks[i]->GetBullet(j)->GetSize().x,
                                        playerTanks[i]->GetBullet(j)->GetSize().y))
                                    {
                                        playerTanks[i]->DestroyBullet(j);

                                        delete destroyableWalls[k][j];
                                        destroyableWalls[k][j] = NULL;

                                        k = maxDestroyableWallRows;
                                        h = maxDestroyableWallColumns;
                                    }
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
            if (enemyTanks[i] != NULL)
            {
                for (short j = 0; j < maxBullets; j++)
                {
                    if (!enemyTanks[i]->IsBulletNull(j))
                    {
                        for (short k = 0; k < maxNonDestroyableWalls; k++)
                        {
                            if (nonDestroyableWalls[k] != NULL)
                            {
                                if (CollisionFunctions::CollisionRectangles(
                                    nonDestroyableWalls[k]->GetXPosition(),
                                    nonDestroyableWalls[k]->GetYPosition(),
                                    nonDestroyableWalls[k]->GetSize().x,
                                    nonDestroyableWalls[k]->GetSize().y,
                                    enemyTanks[i]->GetBullet(j)->GetXPosition(),
                                    enemyTanks[i]->GetBullet(j)->GetYPosition(),
                                    enemyTanks[i]->GetBullet(j)->GetSize().x,
                                    enemyTanks[i]->GetBullet(j)->GetSize().y))
                                {
                                    enemyTanks[i]->DestroyBullet(j);                                    

                                    k = maxNonDestroyableWalls;
                                }
                            }
                        }
                    }

                    if (!enemyTanks[i]->IsBulletNull(j)) 
                    {
                        for (short k = 0; k < maxMapLimitingWalls; k++)
                        {
                            if (mapLimitingWalls[k] != NULL)
                            {
                                if (CollisionFunctions::CollisionRectangles(
                                    mapLimitingWalls[k]->GetXPosition(),
                                    mapLimitingWalls[k]->GetYPosition(),
                                    mapLimitingWalls[k]->GetSize().x,
                                    mapLimitingWalls[k]->GetSize().y,
                                    enemyTanks[i]->GetBullet(j)->GetXPosition(),
                                    enemyTanks[i]->GetBullet(j)->GetYPosition(),
                                    enemyTanks[i]->GetBullet(j)->GetSize().x,
                                    enemyTanks[i]->GetBullet(j)->GetSize().y))
                                {
                                    enemyTanks[i]->DestroyBullet(j);

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
            if (playerTanks[i] != NULL)
            {
                for (short j = 0; j < maxBullets; j++)
                {
                    if (!playerTanks[i]->IsBulletNull(j))
                    {
                        for (short k = 0; k < maxNonDestroyableWalls; k++)
                        {
                            if (nonDestroyableWalls[k] != NULL)
                            {
                                if (CollisionFunctions::CollisionRectangles(
                                    nonDestroyableWalls[k]->GetXPosition(),
                                    nonDestroyableWalls[k]->GetYPosition(),
                                    nonDestroyableWalls[k]->GetSize().x,
                                    nonDestroyableWalls[k]->GetSize().y,
                                    playerTanks[i]->GetBullet(j)->GetXPosition(),
                                    playerTanks[i]->GetBullet(j)->GetYPosition(),
                                    playerTanks[i]->GetBullet(j)->GetSize().x,
                                    playerTanks[i]->GetBullet(j)->GetSize().y))
                                {
                                    playerTanks[i]->DestroyBullet(j);

                                    k = maxNonDestroyableWalls;
                                }
                            }
                        }
                    }

                    if (!playerTanks[i]->IsBulletNull(j))
                    {
                        for (short k = 0; k < maxMapLimitingWalls; k++)
                        {
                            if (mapLimitingWalls[k] != NULL)
                            {
                                if (CollisionFunctions::CollisionRectangles(
                                    mapLimitingWalls[k]->GetXPosition(),
                                    mapLimitingWalls[k]->GetYPosition(),
                                    mapLimitingWalls[k]->GetSize().x,
                                    mapLimitingWalls[k]->GetSize().y,
                                    playerTanks[i]->GetBullet(j)->GetXPosition(),
                                    playerTanks[i]->GetBullet(j)->GetYPosition(),
                                    playerTanks[i]->GetBullet(j)->GetSize().x,
                                    playerTanks[i]->GetBullet(j)->GetSize().y))
                                {
                                    playerTanks[i]->DestroyBullet(j);

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
            if (enemyTanks[i] != NULL) 
            {
                for (short j = 0; j < maxDestroyableWallRows; j++)
                {
                    for (short h = 0; h < maxDestroyableWallColumns; h++) 
                    {
                        if (destroyableWalls[j][h] != NULL)
                        {
                            CollisionFunctions::CollisionTankWithStaticRectangleObject((Tank*)enemyTanks[i],
                                { destroyableWalls[j][h]->GetXPosition(), destroyableWalls[j][h]->GetYPosition() },
                                destroyableWalls[j][h]->GetSize());
                        }
                    }                                       
                }

                for (short j = 0; j < maxNonDestroyableWalls; j++)
                {
                    if (nonDestroyableWalls[j] != NULL)
                    {
                        CollisionFunctions::CollisionTankWithStaticRectangleObject((Tank*)enemyTanks[i],
                            { nonDestroyableWalls[j]->GetXPosition(), nonDestroyableWalls[j]->GetYPosition() },
                            nonDestroyableWalls[j]->GetSize());
                    }
                }

                for (short j = 0; j < maxMapLimitingWalls; j++) 
                {
                    if (mapLimitingWalls[j] != NULL) 
                    {
                        CollisionFunctions::CollisionTankWithStaticRectangleObject((Tank*)enemyTanks[i],
                            { mapLimitingWalls[j]->GetXPosition(), mapLimitingWalls[j]->GetYPosition() },
                            mapLimitingWalls[j]->GetSize());
                    }
                }
            }            
        }       

        for (short i = 0; i < maxPlayers; i++) 
        {
            if (playerTanks[i] != NULL)
            {
                for (short j = 0; j < maxDestroyableWallRows; j++)
                {
                    for (short h = 0; h < maxDestroyableWallColumns; h++) 
                    {
                        if (destroyableWalls[j][h] != NULL)
                        {
                            CollisionFunctions::CollisionTankWithStaticRectangleObject((Tank*)playerTanks[i],
                                { destroyableWalls[j][h]->GetXPosition(), destroyableWalls[j][h]->GetYPosition() },
                                destroyableWalls[j][h]->GetSize());
                        }
                    }                    
                }
            }
        }        

        for (short i = 0; i < maxPlayers; i++)
        {
            if (playerTanks[i] != NULL)
            {
                for (short j = 0; j < maxNonDestroyableWalls; j++)
                {
                    if (nonDestroyableWalls[j] != NULL)
                    {
                        CollisionFunctions::CollisionTankWithStaticRectangleObject((Tank*)playerTanks[i],
                            { nonDestroyableWalls[j]->GetXPosition(), nonDestroyableWalls[j]->GetYPosition() },
                            nonDestroyableWalls[j]->GetSize());
                    }
                }
            }
        }        

        for (short i = 0; i < maxPlayers; i++)
        {
            if (playerTanks[i] != NULL)
            {
                for (short j = 0; j < maxMapLimitingWalls; j++)
                {
                    if (mapLimitingWalls[j] != NULL)
                    {
                        CollisionFunctions::CollisionTankWithStaticRectangleObject((Tank*)playerTanks[i],
                            { mapLimitingWalls[j]->GetXPosition(), mapLimitingWalls[j]->GetYPosition() },
                            mapLimitingWalls[j]->GetSize());
                    }
                }
            }
        }       
    }

    void Gameplay::TanksCollideWithMilitaryBase() 
    {
        for (short i = 0; i < maxEnemyTanks; i++) 
        {
            if (enemyTanks[i] != NULL && militaryBase != NULL) 
            {
                CollisionFunctions::CollisionTankWithStaticRectangleObject((Tank*)enemyTanks[i], { militaryBase->GetXPosition(),
                    militaryBase->GetYPosition() }, militaryBase->GetSize());
            }
        }

        for (short i = 0; i < maxPlayers; i++)
        {
            if (playerTanks[i] != NULL && militaryBase != NULL)
            {
                CollisionFunctions::CollisionTankWithStaticRectangleObject((Tank*)playerTanks[i], { militaryBase->GetXPosition(),
                    militaryBase->GetYPosition() }, militaryBase->GetSize());
            }
        }        
    }

    void Gameplay::TanksCollideWithEachOther() 
    {
        for (short i = 0; i < maxPlayers; i++)
        {
            if (playerTanks[i] != NULL) 
            {
                for (short j = 0; j < maxEnemyTanks; j++)
                {
                    if (enemyTanks[j] != NULL)
                    {
                        CollisionFunctions::TanksCollision((Tank*)playerTanks[i], (Tank*)enemyTanks[j]);
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
            if (enemyTanks[i] != NULL) 
            {
                allDestroyed = false;

                i = maxEnemyTanks;
            }
        }

        return allDestroyed;
    }

    void Gameplay::DestroyPlayerTankIfHasNoLifesLeft(short index)
    {
        if (playerTanks[index]->GetLifes() <= 0) 
        {
            delete playerTanks[index];
            playerTanks[index] = NULL;
        }
    }

    void Gameplay::DrawTanksMoveKeysUI()
    {
        for (short i = 0; i < numberOfPlayers; i++) 
        {
            switch (i)
            {
            case 0:                
                window.draw(inputKeysUISprites[13]);
                window.draw(inputKeysUISprites[11]);
                window.draw(inputKeysUISprites[14]);
                window.draw(inputKeysUISprites[18]);
                window.draw(inputKeysUISprites[2]);
                break;
            case 1:
                window.draw(inputKeysUISprites[10]);
                window.draw(inputKeysUISprites[0]);
                window.draw(inputKeysUISprites[1]);
                window.draw(inputKeysUISprites[19]);
                window.draw(inputKeysUISprites[15]);                
                break;
            case 2:
                window.draw(inputKeysUISprites[16]);
                window.draw(inputKeysUISprites[3]);
                window.draw(inputKeysUISprites[5]);
                window.draw(inputKeysUISprites[17]);
                window.draw(inputKeysUISprites[4]);                
                break;
            case 3:
                window.draw(inputKeysUISprites[12]);
                window.draw(inputKeysUISprites[7]);
                window.draw(inputKeysUISprites[9]);
                window.draw(inputKeysUISprites[6]);
                window.draw(inputKeysUISprites[8]);
                break;            
            }                      
        }        
    }

    void Gameplay::DrawHearts() 
    {
        short aux = 0;

        for (short i = 0; i <  maxPlayers; i++) 
        {
            if (playerTanks[i] != NULL) 
            {
                for (short j = 0; j < playerTanks[i]->GetLifes(); j++)
                {                    
                    heartsSprites[i].setPosition(limitingWallXOffset + (heartsSpriteSize.x * aux) + (heartsSpritesSeparation.x * (aux + 1)) + (heartsSpritesSeparation.y*i), heartsSpritesSeparation.y);
                    
                    window.draw(heartsSprites[i]);

                    aux += 1;
                }
            }
        }
    }   
}
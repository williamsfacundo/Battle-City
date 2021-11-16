#include "enemy.h"

#include <SFML/System/String.hpp>

#include "tank.h"

namespace Battle_City 
{
	Enemy::Enemy(float xPosition, float yPosition, Vector2f size, Color color, const String imageFiles[maxTextures]) : Tank(xPosition, yPosition, size, color, imageFiles)
	{
		moveTimer = GetRandomTimer(minMoveTimer, maxMoveTimer);
		shootingTimer = GetRandomTimer(minShootingTimer, maxShootingTimer);		
	}

	void Enemy::Update(Time dt, float xLimit, float yLimit)
	{
		UpdateTimer(dt, moveTimer);
		UpdateTimer(dt, shootingTimer);

		MoveTank(dt);
		MoveBullets(dt);			
		DestroyBulletsOutOfMapLimits(xLimit, yLimit);		
		Shoot();
	}

	void Enemy::Shoot()
	{
		if (shootingTimer == 0.0f) 
		{
			if (FindEmpyBulletIndex() != maxBullets)
			{
				float xPos = 0.0f;
				float yPos = 0.0f;

				switch (getDirection())
				{
				case Direction::left:

					xPos = GetXPosition();
					yPos = GetYPosition() + (GetSize().y / 2.0f) - (bulletsHeight / 2.0f);
					break;
				case Direction::right:

					xPos = GetXPosition() + GetSize().x;
					yPos = GetYPosition() + (GetSize().y / 2.0f) - (bulletsHeight / 2.0f);
					break;
				case Direction::up:

					xPos = GetXPosition() + (GetSize().x / 2) - (bulletsWidth / 2.0f);
					yPos = GetYPosition();
					break;
				case Direction::down:

					xPos = GetXPosition() + (GetSize().x / 2) - (bulletsWidth / 2.0f);
					yPos = GetYPosition() + GetSize().y;
					break;
				}

				CreateBullet(FindEmpyBulletIndex(), xPos, yPos);

				shootingTimer = GetRandomTimer(minShootingTimer, maxShootingTimer);
			}
		}
	}	

	void Enemy::MoveTank(Time dt) 
	{
		if (moveTimer == 0.0f) 
		{
			switch (GetRandomDirection())
			{
			case Direction::left:

				setDirection(Direction::left);
				SetMoveSpeed(-enemyMoveSpeed * dt.asSeconds());
				AddXPosition(-enemyMoveSpeed * dt.asSeconds());
				break;
			case Direction::right:
								
				setDirection(Direction::right);
				SetMoveSpeed(enemyMoveSpeed * dt.asSeconds());
				AddXPosition(enemyMoveSpeed * dt.asSeconds());
				break;
			case Direction::up:

				AddYPosition(-enemyMoveSpeed * dt.asSeconds());
				SetMoveSpeed(-enemyMoveSpeed * dt.asSeconds());
				setDirection(Direction::up);
				break;
			case Direction::down:

				AddYPosition(enemyMoveSpeed * dt.asSeconds());
				SetMoveSpeed(enemyMoveSpeed * dt.asSeconds());
				setDirection(Direction::down);
				break;
			default:

				setDirection(Direction::left);
				break;
			}

			SetRectanglePosition(GetXPosition(), GetYPosition());
			SetSpritePosition(GetXPosition(), GetYPosition());
			SetSpriteDependingDirection();
			UpdateSpriteSize();
			moveTimer = maxMoveTimer;
		}		
	}

	Direction Enemy::GetRandomDirection() 
	{
		Direction direction;

		short i = rand() % 4;

		switch (i)
		{
		case 0:
			direction = Direction::left;
			break;
		case 1:
			direction = Direction::right;
			break;
		case 2:
			direction = Direction::up;
			break;		
		case 3:
			direction = Direction::down;
			break;
		default:
			direction = Direction::left;
			break;
		}

		return direction;
	}

	float Enemy::GetRandomTimer(float min, float max)
	{
		return static_cast<float>(rand() % static_cast<short>(max - min) + static_cast<short>(min));
	}
}
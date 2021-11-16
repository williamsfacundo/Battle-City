#include "enemy.h"

#include <SFML/System/String.hpp>

#include "tank.h"

namespace Battle_City 
{
	Enemy::Enemy(float xPosition, float yPosition, Vector2f size, Color color, String imageFiles[maxTextures]) : Tank(xPosition, yPosition, size, color, imageFiles)
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
		Shoot();		
		DestroyBulletsOutOfMapLimits(xLimit, yLimit);
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
					yPos = GetYPosition() + (getSize().y / 2.0f) - (bulletsHeight / 2.0f);
					break;
				case Direction::right:

					xPos = GetXPosition() + getSize().x;
					yPos = GetYPosition() + (getSize().y / 2.0f) - (bulletsHeight / 2.0f);
					break;
				case Direction::up:

					xPos = GetXPosition() + (getSize().x / 2) - (bulletsWidth / 2.0f);
					yPos = GetYPosition();
					break;
				case Direction::down:

					xPos = GetXPosition() + (getSize().x / 2) - (bulletsWidth / 2.0f);
					yPos = GetYPosition() + getSize().y;
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
				AddXPosition(-enemyMoveSpeed * dt.asSeconds());
				break;
			case Direction::right:

				setDirection(Direction::right);
				AddXPosition(enemyMoveSpeed * dt.asSeconds());
				break;
			case Direction::up:

				AddYPosition(-enemyMoveSpeed * dt.asSeconds());
				setDirection(Direction::up);
				break;
			case Direction::down:

				AddYPosition(enemyMoveSpeed * dt.asSeconds());
				setDirection(Direction::down);
				break;
			default:

				setDirection(Direction::left);
				break;
			}

			SetRectanglePosition(GetXPosition(), GetYPosition());
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
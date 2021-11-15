#include "tank.h"

#include "SFML/Window/Keyboard.hpp"
#include "SFML/System/Time.hpp"

#include "game_object.h"

namespace Battle_City
{
	Tank::Tank(float xPosition, float yPosition, Vector2f size) : GameObject(xPosition, yPosition)
	{
		SetSize(size.x, size.y);
		rectangle.setSize(size);
		rectangle.setFillColor(tankColor);
		rectangle.setPosition(xPosition, yPosition);
		moveStatus = PlayerMovementSet::none;
		direction = Direction::up;
		shootingTimer = 0.0f;

		InitBullets();
	}

	Tank::~Tank()
	{
		DestroyBullets();
	}

	void Tank::SetSize(float width, float heigth)
	{
		size.x = width;
		size.y = heigth;
	}

	Vector2f Tank::GetSize()
	{
		return size;
	}

	void Tank::Input()
	{
		MovementInput();
		Shoot();
	}

	void Tank::Update(Time dt, float xLimit, float yLimit)
	{
		MovePlayer(dt);
		MoveBullets(dt);
		UpdateTimer(dt);
		DestroyBulletsOutOfMapLimits(xLimit, yLimit);
	}

	void Tank::Draw(RenderWindow& window)
	{
		window.draw(rectangle);

		DrawBullets(window);
	}

	void Tank::MovementInput()
	{
		if (Keyboard::isKeyPressed(moveLeft))
		{
			moveStatus = PlayerMovementSet::left;
			direction = Direction::left;
		}
		else if (Keyboard::isKeyPressed(moveRight))
		{
			moveStatus = PlayerMovementSet::right;
			direction = Direction::right;
		}
		else if (Keyboard::isKeyPressed(moveUp))
		{
			moveStatus = PlayerMovementSet::up;
			direction = Direction::up;
		}
		else if (Keyboard::isKeyPressed(moveDown))
		{
			moveStatus = PlayerMovementSet::down;
			direction = Direction::down;
		}
		else
		{
			moveStatus = PlayerMovementSet::none;
		}
	}

	void Tank::MovePlayer(Time dt)
	{
		switch (moveStatus)
		{
		case PlayerMovementSet::right:

			AddXPosition(tankMoveSpeed * dt.asSeconds());
			break;
		case PlayerMovementSet::left:

			AddXPosition(-tankMoveSpeed * dt.asSeconds());
			break;
		case PlayerMovementSet::up:

			AddYPosition(-tankMoveSpeed * dt.asSeconds());
			break;
		case PlayerMovementSet::down:

			AddYPosition(tankMoveSpeed * dt.asSeconds());
			break;
		case PlayerMovementSet::none:
			break;
		default:
			break;
		}

		rectangle.setPosition(GetXPosition(), GetYPosition());
	}

	void Tank::InitBullets()
	{
		for (short i = 0; i < maxBullets; i++)
		{
			bullets[i] = NULL;
		}
	}

	void Tank::DestroyBullet(short index)
	{
		if (bullets[index] != NULL)
		{
			delete bullets[index];
			bullets[index] = NULL;
		}
	}

	void Tank::DestroyBullets()
	{
		for (short i = 0; i < maxBullets; i++)
		{
			DestroyBullet(i);
		}
	}

	short Tank::FindEmpyBulletIndex()
	{
		short auxReturn = maxBullets;

		for (short i = 0; i < maxBullets; i++)
		{
			if (bullets[i] == NULL)
			{
				return i;
			}
		}

		return auxReturn;
	}

	void Tank::Shoot()
	{
		if (Keyboard::isKeyPressed(shootKey) && shootingTimer == 0.0f)
		{
			if (FindEmpyBulletIndex() != maxBullets)
			{
				float xPos = 0.0f;
				float yPos = 0.0f;

				switch (direction)
				{
				case Direction::left:

					xPos = GetXPosition();
					yPos = GetYPosition() + (size.y / 2.0f) - (bulletsHeight / 2.0f);
					break;
				case Direction::right:

					xPos = GetXPosition() + size.x;
					yPos = GetYPosition() + (size.y / 2.0f) - (bulletsHeight / 2.0f);
					break;
				case Direction::up:

					xPos = GetXPosition() + (size.x / 2) - (bulletsWidth / 2.0f);
					yPos = GetYPosition();
					break;
				case Direction::down:

					xPos = GetXPosition() + (size.x / 2) - (bulletsWidth / 2.0f);
					yPos = GetYPosition() + size.y;
					break;
				}

				bullets[FindEmpyBulletIndex()] = new Bullet(xPos, yPos, { bulletsWidth, bulletsHeight }, direction);

				shootingTimer = timeBetweenShots;
			}
		}
	}

	void Tank::MoveBullets(Time dt)
	{
		for (short i = 0; i < maxBullets; i++)
		{
			if (bullets[i] != NULL)
			{
				((Bullet*)bullets[i])->MoveBullet(dt);
			}
		}
	}

	void Tank::DrawBullets(RenderWindow& window)
	{
		for (short i = 0; i < maxBullets; i++)
		{
			if (bullets[i] != NULL)
			{
				((Bullet*)bullets[i])->Draw(window);
			}
		}
	}

	void Tank::DestroyBulletsOutOfMapLimits(float xLimit, float yLimit)
	{
		for (short i = 0; i < maxBullets; i++)
		{
			if (bullets[i] != NULL)
			{
				if (((Bullet*)bullets[i])->BulletOutOfMapLimits(xLimit, yLimit))
				{
					DestroyBullet(i);
				}
			}
		}
	}

	void Tank::UpdateTimer(Time dt)
	{
		if (shootingTimer > 0.0f)
		{
			shootingTimer -= dt.asSeconds();
		}

		if (shootingTimer < 0.0f)
		{
			shootingTimer = 0.0f;
		}
	}
}

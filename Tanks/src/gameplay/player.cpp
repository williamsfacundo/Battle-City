#include "player.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace Battle_City 
{
	Player::Player(float xPosition, float yPosition, Vector2f size, Color color) : Tank(xPosition, yPosition, size, color)
	{
		shootingTimer = 0.0f;
	}

	Player::~Player() 
	{

	}

	void Player::Input()
	{
		MovementInput();
		Shoot();
	}

	void Player::Update(Time dt, float xLimit, float yLimit)
	{
		MovePlayer(dt);
		MoveBullets(dt);
		UpdateTimer(dt);
		DestroyBulletsOutOfMapLimits(xLimit, yLimit);
	}

	void Player::Shoot()
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

	void Player::MovementInput()
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

	void Player::UpdateTimer(Time dt)
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

	void Player::MovePlayer(Time dt)
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
}
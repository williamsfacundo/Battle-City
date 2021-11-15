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

				shootingTimer = timeBetweenShots;
			}
		}
	}

	void Player::MovementInput()
	{
		if (Keyboard::isKeyPressed(moveLeft))
		{
			setMoveStatus(PlayerMovementSet::left);
			setDirection(Direction::left);
		}
		else if (Keyboard::isKeyPressed(moveRight))
		{
			setMoveStatus(PlayerMovementSet::right);
			setDirection(Direction::right);
		}
		else if (Keyboard::isKeyPressed(moveUp))
		{
			setMoveStatus(PlayerMovementSet::up);
			setDirection(Direction::up);
		}
		else if (Keyboard::isKeyPressed(moveDown))
		{
			setMoveStatus(PlayerMovementSet::down);
			setDirection(Direction::down);
		}
		else
		{
			setMoveStatus(PlayerMovementSet::none);
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
		switch (GetMoveStatus())
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

		SetRectanglePosition(GetXPosition(), GetYPosition());
	}	
}
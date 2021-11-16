#include "player.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace Battle_City 
{
	Player::Player(float xPosition, float yPosition, Vector2f size, Color color) : Tank(xPosition, yPosition, size, color)
	{
		shootingTimer = 0.0f;
		moveStatus = PlayerMovementSet::none;		
		lifes = initialLifes;
	}

	Player::~Player() 
	{

	}

	void Player::DecreaseLifes() 
	{
		lifes -= 1;
	}

	void Player::setMoveStatus(PlayerMovementSet moveStatus)
	{
		this->moveStatus = moveStatus;
	}

	PlayerMovementSet Player::GetMoveStatus()
	{
		return moveStatus;
	}

	short Player::GetLifes() 
	{
		return lifes;
	}

	void Player::Input()
	{
		MovementInput();
		Shoot();
	}

	void Player::Update(Time dt, float xLimit, float yLimit)
	{
		MoveTank(dt);
		MoveBullets(dt);
		UpdateTimer(dt, shootingTimer);
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

	void Player::MoveTank(Time dt)
	{
		switch (GetMoveStatus())
		{
		case PlayerMovementSet::right:

			AddXPosition(playerMoveSpeed * dt.asSeconds());
			break;
		case PlayerMovementSet::left:

			AddXPosition(-playerMoveSpeed * dt.asSeconds());
			break;
		case PlayerMovementSet::up:

			AddYPosition(-playerMoveSpeed * dt.asSeconds());
			break;
		case PlayerMovementSet::down:

			AddYPosition(playerMoveSpeed * dt.asSeconds());
			break;
		case PlayerMovementSet::none:
			break;
		default:
			break;
		}

		SetRectanglePosition(GetXPosition(), GetYPosition());
	}	
}
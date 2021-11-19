#include "player.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;

namespace Battle_City 
{
	Player::Player(float xPosition, float yPosition, Vector2f size, Color color, const String imageFiles[maxTextures], const Keyboard::Key inputKeys[maxInputKeys]) : Tank(xPosition, yPosition, size, color, imageFiles)
	{
		moveStatus = PlayerMovementSet::none;

		for (short i = 0; i < maxInputKeys; i++) 
		{
			this->inputKeys[i] = inputKeys[i];
		}
		
		shootingTimer = 0.0f;			
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

	Keyboard::Key Player::GetInputKeys(short index)
	{
		return inputKeys[index];
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
		SetTankMoving(IsTankMoving());
	}

	void Player::Shoot()
	{
		if (Keyboard::isKeyPressed(inputKeys[0]) && shootingTimer == 0.0f)
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

				shootingTimer = timeBetweenShots;
			}
		}
	}

	void Player::MovementInput()
	{		
		if (Keyboard::isKeyPressed(inputKeys[1]))
		{		
			setMoveStatus(PlayerMovementSet::left);			
		}
		else if (Keyboard::isKeyPressed(inputKeys[2]))
		{
			setMoveStatus(PlayerMovementSet::right);			
		}
		else if (Keyboard::isKeyPressed(inputKeys[3]))
		{
			setMoveStatus(PlayerMovementSet::up);			
		}
		else if (Keyboard::isKeyPressed(inputKeys[4]))
		{
			setMoveStatus(PlayerMovementSet::down);			
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

			SetMoveSpeed(playerMoveSpeed * dt.asSeconds());
			AddXPosition(playerMoveSpeed * dt.asSeconds());

			if (getDirection() != Direction::right) 
			{
				setDirection(Direction::right);
				SetSpriteDependingDirection();
			}

			break;
		case PlayerMovementSet::left:

			SetMoveSpeed(-playerMoveSpeed * dt.asSeconds());
			AddXPosition(-playerMoveSpeed * dt.asSeconds());
			
			if (getDirection() != Direction::left)
			{
				setDirection(Direction::left);
				SetSpriteDependingDirection();
			}

			break;
		case PlayerMovementSet::up:

			SetMoveSpeed(-playerMoveSpeed * dt.asSeconds());
			AddYPosition(-playerMoveSpeed * dt.asSeconds());
			
			if (getDirection() != Direction::up)
			{
				setDirection(Direction::up);
				SetSpriteDependingDirection();
			}
			
			break;
		case PlayerMovementSet::down:			
			
			SetMoveSpeed(playerMoveSpeed * dt.asSeconds());
			AddYPosition(playerMoveSpeed * dt.asSeconds());

			if (getDirection() != Direction::down)
			{
				setDirection(Direction::down);
				SetSpriteDependingDirection();
			}

			break;
		case PlayerMovementSet::none:
			break;
		default:
			break;
		}

		if (GetMoveStatus() != PlayerMovementSet::none)
		{
			SetRectanglePosition(GetXPosition(), GetYPosition());
			SetSpritePosition(GetXPosition(), GetYPosition());				
			Animation(dt);
		}		
	}	

	bool Player::IsTankMoving() 
	{
		return moveStatus != PlayerMovementSet::none;
	}
}
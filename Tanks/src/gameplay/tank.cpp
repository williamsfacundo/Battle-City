#include "tank.h"

#include "SFML/Window/Keyboard.hpp"
#include "SFML/System/Time.hpp"

#include "game_object.h"

Tank::Tank(float xPosition, float yPosition, Vector2f size) : GameObject(xPosition, yPosition)
{
	SetSize(size.x, size.y);
	rectangle.setSize(size);
	rectangle.setFillColor(tankColor);
	rectangle.setPosition(xPosition, yPosition);
	moveStatus = PlayerMovementSet::none;
	direction = Direction::up;

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
}

void Tank::Update(Time dt)
{	
	MovePlayer(dt);
}

void Tank::Draw(RenderWindow& window)
{
	window.draw(rectangle);
}

void Tank::MovementInput() 
{
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		moveStatus = PlayerMovementSet::left;
		direction = Direction::left;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		moveStatus = PlayerMovementSet::right;
		direction = Direction::right;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		moveStatus = PlayerMovementSet::up;
		direction = Direction::up;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
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
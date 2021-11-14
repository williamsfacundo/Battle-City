#include "tank.h"

#include "SFML/Window/Keyboard.hpp"
#include "SFML/System/Time.hpp"

Tank::Tank(float xPosition, float yPosition, Vector2f size) : GameObject(xPosition, yPosition)
{
	SetSize(size.x, size.y);
	rectangle.setSize(size);
	rectangle.setFillColor(Color::Green);
	rectangle.setPosition(xPosition, yPosition);
	moveStatus = PlayerMovementSet::none;
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
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		moveStatus = PlayerMovementSet::right;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		moveStatus = PlayerMovementSet::up;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		moveStatus = PlayerMovementSet::down;
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

		AddXPosition(moveValue * dt.asSeconds());
		break;
	case PlayerMovementSet::left:
		
		AddXPosition(-moveValue * dt.asSeconds());
		break;
	case PlayerMovementSet::up:
		
		AddYPosition(-moveValue * dt.asSeconds());
		break;
	case PlayerMovementSet::down:
		
		AddYPosition(moveValue * dt.asSeconds());
		break;
	case PlayerMovementSet::none:
		break;
	default:
		break;
	}

	rectangle.setPosition(GetXPosition(), GetYPosition());
}
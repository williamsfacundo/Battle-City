#include "bullet.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

#include "game_object.h"

namespace Battle_City
{
	Bullet::Bullet(float xPosition, float yPosition, Vector2f size, Direction direction) : GameObject(xPosition, yPosition)
	{
		SetSize(size.x, size.y);
		rectangle.setSize(size);
		rectangle.setFillColor(bulletColor);
		rectangle.setPosition(xPosition, yPosition);

		this->direction = direction;
	}

	void Bullet::SetSize(float width, float heigth)
	{
		size.x = width;
		size.y = heigth;
	}

	Vector2f Bullet::GetSize()
	{
		return size;
	}

	void Bullet::Update(Time dt)
	{
		MoveBullet(dt);
	}

	void Bullet::Draw(RenderWindow& window)
	{
		window.draw(rectangle);
	}

	void Bullet::MoveBullet(Time dt)
	{
		switch (direction)
		{
		case Direction::left:

			AddXPosition(-bulletMoveSpeed * dt.asSeconds());
			break;
		case Direction::right:

			AddXPosition(bulletMoveSpeed * dt.asSeconds());
			break;
		case Direction::up:

			AddYPosition(-bulletMoveSpeed * dt.asSeconds());
			break;
		case Direction::down:

			AddYPosition(bulletMoveSpeed * dt.asSeconds());
			break;
		}

		rectangle.setPosition(GetXPosition(), GetYPosition());
	}

	bool Bullet::BulletOutOfMapLimits(float xLimit, float yLimit)
	{
		return (GetXPosition() < 0 || GetXPosition() > xLimit) || (GetYPosition() < 0 || GetYPosition() > yLimit);
	}
}
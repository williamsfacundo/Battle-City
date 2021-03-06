#include "bullet.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

#include "rectangle.h"
#include "global_vars.h"

namespace Battle_City
{
	Bullet::Bullet(float xPosition, float yPosition, Vector2f size, Direction direction) : Rectangle(xPosition, yPosition, size)
	{
		SetSize(size.x, size.y);
		rectangle.setSize(size);
		rectangle.setFillColor(bulletColor);		
		rectangle.setPosition(xPosition, yPosition);

		this->direction = direction;

		SetBulletSpriteDependingDirection(direction);		

		bulletSprite.setTexture(bulletTexture);
		bulletSprite.setPosition(xPosition, yPosition);		

		Vector2f actualSize;

		actualSize.x = static_cast<float>(bulletSprite.getTextureRect().width);
		actualSize.y = static_cast<float>(bulletSprite.getTextureRect().height);

		bulletSprite.setScale(size.x / actualSize.x, size.y / actualSize.y);
		
	}	

	void Bullet::SetBulletSpriteDependingDirection(Direction direction)
	{
		switch (direction)
		{
		case Battle_City::Direction::left:
			bulletTexture.loadFromFile("assets/bullet/bulletSpriteLeft.png");
			break;
		case Battle_City::Direction::right:
			bulletTexture.loadFromFile("assets/bullet/bulletSpriteRight.png");
			break;
		case Battle_City::Direction::up:
			bulletTexture.loadFromFile("assets/bullet/bulletSpriteUp.png");
			break;
		case Battle_City::Direction::down:
			bulletTexture.loadFromFile("assets/bullet/bulletSpriteDown.png");			
			break;
		}
	}	

	void Bullet::Update(Time dt)
	{
		MoveBullet(dt);
	}

	void Bullet::Draw(RenderWindow& window)
	{
#if _DEBUG
		window.draw(rectangle);
#endif
		window.draw(bulletSprite);
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
		bulletSprite.setPosition(GetXPosition(), GetYPosition());
	}

	bool Bullet::BulletOutOfMapLimits(float xLimit, float yLimit)
	{
		return (GetXPosition() < 0 || GetXPosition() > xLimit) || (GetYPosition() < 0 || GetYPosition() > yLimit);
	}	
}
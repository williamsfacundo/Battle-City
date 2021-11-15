#include "tank.h"

#include <iostream>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "game_object.h"

namespace Battle_City
{
	Tank::Tank(float xPosition, float yPosition, Vector2f size, Color color) : GameObject(xPosition, yPosition)
	{
		SetSize(size.x, size.y);
		rectangle.setSize(size);
		rectangle.setFillColor(color);
		rectangle.setPosition(xPosition, yPosition);		
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

	void Tank::setDirection(Direction direction) 
	{
		this->direction = direction;
	}

	void Tank::SetRectanglePosition(float xPos, float yPos) 
	{
		rectangle.setPosition(xPos, yPos);
	}

	Vector2f Tank::GetSize()
	{
		return size;
	}		

	Direction Tank::getDirection() 
	{
		return direction;
	}

	Vector2f Tank::getSize() 
	{
		return size;
	}	

	RectangleShape Tank::GetRectangle() 
	{
		return rectangle;
	}

	void Tank::Draw(RenderWindow& window)
	{
		window.draw(rectangle);

		DrawBullets(window);
	}

	void Tank::UpdateTimer(Time dt, float& timer) 
	{
		if (timer > 0.0f)
		{
			timer -= dt.asSeconds();
		}

		if (timer < 0.0f)
		{
			timer = 0.0f;
		}
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

	void Tank::CreateBullet(short index, float xPos, float yPos) 
	{
		bullets[index] = new Bullet(xPos, yPos, { bulletsWidth, bulletsHeight }, getDirection());
	}

	GameObject* Tank::GetBullet(short index)
	{
		return bullets[index];
	}

	bool Tank::IsBulletNull(short index)
	{
		return bullets[index] == NULL;
	}
}

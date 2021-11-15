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

	void Tank::Draw(RenderWindow& window)
	{
		window.draw(rectangle);

		DrawBullets(window);
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
}

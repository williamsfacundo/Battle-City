#include "wall.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "game_object.h"

namespace Battle_City 
{
	Wall::Wall(float xPosition, float yPosition, Vector2f size, bool destroyable) : GameObject(xPosition, yPosition)
	{
		if (destroyable)
		{
			color = destroyableWallColor;
		}
		else
		{
			color = nonDestroyableWallColor;
		}

		SetSize(size.x, size.y);
		rectangle.setSize(size);
		this->destroyable = destroyable;		
		rectangle.setFillColor(color);
		rectangle.setPosition(xPosition, yPosition);		
	}

	void Wall::SetSize(float width, float heigth)
	{
		size.x = width;
		size.y = heigth;
	}

	Vector2f Wall::GetSize()
	{
		return size;
	}

	bool Wall::GetDestroyable() 
	{
		return destroyable;
	}

	void Wall::Draw(RenderWindow& window)
	{
		window.draw(rectangle);
	}
}
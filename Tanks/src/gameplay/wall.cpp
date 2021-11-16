#include "wall.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "game_object.h"

namespace Battle_City 
{
	Wall::Wall(float xPosition, float yPosition, Vector2f size, const String textureFile, bool destroyable) : GameObject(xPosition, yPosition)
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
		wallTexture.loadFromFile(textureFile);
		wallSprite.setTexture(wallTexture);
		wallSprite.setPosition(xPosition, yPosition);

		Vector2f actualSize;

		actualSize.x = wallSprite.getTextureRect().width;
		actualSize.y = wallSprite.getTextureRect().height;

		wallSprite.setScale(size.x / actualSize.x, size.y / actualSize.y);
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
#if _Debug
		window.draw(rectangle);
#endif
		window.draw(wallSprite);		
	}
}
#include "base.h"

#include <SFML/Graphics/RenderWindow.hpp>

#include "game_object.h"

namespace Battle_City
{
	Base::Base(float xPosition, float yPosition, Vector2f size) : GameObject (xPosition, yPosition)
	{
		SetSize(size.x, size.y);
		rectangle.setSize(size);
		color = baseColor;
		rectangle.setFillColor(color);
		rectangle.setPosition(xPosition, yPosition);		
	}

	void Base::SetSize(float width, float heigth)
	{
		size.x = width;
		size.y = heigth;
	}

	Vector2f Base::GetSize() 
	{
		return size;
	}

	void Base::Draw(RenderWindow& window) 
	{
		window.draw(rectangle);
	}
}
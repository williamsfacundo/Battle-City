#include "rectangle.h"

namespace Battle_City
{
	Rectangle::Rectangle(float xPosition, float yPosition, Vector2f size)
	{
		SetPosition(xPosition, yPosition);
		SetSize(size.x, size.y);
	}

	Rectangle::~Rectangle() 
	{

	}

	void Rectangle::SetPosition(float xPosition, float yPosition)
	{
		this->xPosition = xPosition;
		this->yPosition = yPosition;
	}

	void Rectangle::SetSize(float width, float heigth)
	{
		size.x = width;
		size.y = heigth;
	}		

	Vector2f Rectangle::GetSize()
	{
		return size;
	}

	void Rectangle::AddXPosition(float value)
	{
		xPosition += value;
	}

	void Rectangle::AddYPosition(float value)
	{
		yPosition += value;
	}	

	float Rectangle::GetXPosition()
	{
		return xPosition;
	}

	float Rectangle::GetYPosition()
	{
		return yPosition;
	}
}
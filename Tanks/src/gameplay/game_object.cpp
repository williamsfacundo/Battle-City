#include "game_object.h"

GameObject::GameObject(float xPosition, float yPosition)
{
	SetPosition(xPosition, yPosition);
}

void GameObject::SetPosition(float xPosition, float yPosition) 
{
	this->xPosition = xPosition;
	this->yPosition = yPosition;
}

float GameObject::GetXPosition() 
{
	return xPosition;
}

float GameObject::GetYPosition() 
{
	return yPosition;
}
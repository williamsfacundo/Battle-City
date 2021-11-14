#include "game_object.h"

GameObject::GameObject(float xPosition, float yPosition)
{
	SetPosition(xPosition, yPosition);
}

GameObject::~GameObject() 
{

}

void GameObject::SetPosition(float xPosition, float yPosition) 
{
	this->xPosition = xPosition;
	this->yPosition = yPosition;
}

void GameObject::AddXPosition(float value)
{
	xPosition += value;
}

void GameObject::AddYPosition(float value)
{
	yPosition += value;
}

float GameObject::GetXPosition() 
{
	return xPosition;
}

float GameObject::GetYPosition() 
{
	return yPosition;
}
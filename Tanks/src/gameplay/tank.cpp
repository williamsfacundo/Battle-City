#include "tank.h"

Tank::Tank(float xPosition, float yPosition, Vector2f size) : GameObject(xPosition, yPosition)
{
	SetSize(size.x, size.y);
	rectangle.setSize(size);
	rectangle.setFillColor(Color::Green);
}
Tank::~Tank() 
{

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

void Tank::Input() 
{

}
void Tank::Update() 
{
	
}
void Tank::Draw(RenderWindow window)
{
	window.draw(rectangle);
}
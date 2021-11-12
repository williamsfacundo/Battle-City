#ifndef TANK_H
#define TANK_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

#include "game_object.h"

using namespace sf;

class Tank : public GameObject
{
private:
	Vector2f size;
	RectangleShape rectangle;	
public:
	Tank(float xPosition, float yPosition, Vector2f size);	
	
	void SetSize(float width, float heigth);
	Vector2f GetSize();

	void Input();
	void Update();
	virtual void Draw(RenderWindow& window);	
};

#endif

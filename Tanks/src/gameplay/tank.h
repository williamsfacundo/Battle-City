#ifndef tank_h
#define tank_h

#include "SFML/Graphics.hpp"
#include "game_object.h"

using namespace sf;

class Tank : public GameObject
{
private:
	Vector2f size;
	RectangleShape rectangle;
public:
	Tank(float xPosition, float yPosition, Vector2f size);
	~Tank();
	
	void SetSize(float width, float heigth);
	Vector2f GetSize();

	void Input();
	void Update();
	virtual void Draw(RenderWindow window);
};

#endif

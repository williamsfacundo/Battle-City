#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "SFML/Graphics/RenderWindow.hpp"

using namespace sf;

enum class Direction {left, right, up, down};

class GameObject 
{
private:
	float xPosition;
	float yPosition;	
protected:
	void AddXPosition(float value);
	void AddYPosition(float value);
public:
	GameObject(float xPosition, float yPosition);	

	void SetPosition(float xPosition, float yPosition);	

	float GetXPosition();
	float GetYPosition();

	virtual void Draw(RenderWindow& window) = 0;	
};

#endif

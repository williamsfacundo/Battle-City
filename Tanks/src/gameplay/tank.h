#ifndef TANK_H
#define TANK_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Time.hpp"

#include "game_object.h"

using namespace sf;

enum class PlayerMovementSet {right, left, up, down, none};
const float tankMoveSpeed = 150.5f;
const Color tankColor = Color::Green;

class Tank : public GameObject
{
private:
	Vector2f size;
	RectangleShape rectangle;	
	PlayerMovementSet moveStatus;
	Direction direction;	
public:
	Tank(float xPosition, float yPosition, Vector2f size);	
	
	void SetSize(float width, float heigth);
	Vector2f GetSize();

	void Input();
	void Update(Time dt);
	virtual void Draw(RenderWindow& window);	

	void MovementInput();
	void MovePlayer(Time dt);
};

#endif

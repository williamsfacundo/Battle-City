#ifndef TANK_H
#define TANK_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Time.hpp"

#include "game_object.h"
#include "bullet.h"

using namespace sf;

enum class PlayerMovementSet {right, left, up, down, none};
const float tankMoveSpeed = 150.5f;
const Color tankColor = Color::Green;
const short maxBullets = 6;

class Tank : public GameObject
{
private:
	Vector2f size;
	RectangleShape rectangle;	
	PlayerMovementSet moveStatus;
	Direction direction;
	GameObject* bullets[maxBullets];
public:
	Tank(float xPosition, float yPosition, Vector2f size);		
	~Tank();
	
	void SetSize(float width, float heigth);
	Vector2f GetSize();

	void Input();
	void Update(Time dt);
	virtual void Draw(RenderWindow& window);	

	void MovementInput();
	void MovePlayer(Time dt);

	void InitBullets();
	void DestroyBullet(short index);
	void DestroyBullets();
};

#endif

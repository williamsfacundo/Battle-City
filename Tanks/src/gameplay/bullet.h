#ifndef BULLET_H
#define BULLET_H

#include "game_object.h"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Time.hpp"

const float bulletMoveSpeed = 300.0f;
const Color bulletColor = Color::Red;

class Bullet : public GameObject 
{
private:
	Vector2f size;
	RectangleShape rectangle;
	Direction direction;	
public:
	Bullet(float xPosition, float yPosition, Vector2f size, Direction direction);

	void SetSize(float width, float heigth);
	Vector2f GetSize();

	void Update(Time dt);
	virtual void Draw(RenderWindow& window);

	void MoveBullet(Time dt);

	bool BulletOutOfMapLimits(float xLimit, float yLimit);
};

#endif

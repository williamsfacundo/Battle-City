#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/System/Time.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#include "tank.h"

namespace Battle_City 
{
	const Color enemyTankColor = Color::Yellow;	

	const float enemyMoveSpeed = 650.5f;
	const float minMoveTimer = 1.0f;
	const float maxMoveTimer = 3.0f;
	const float minShootingTimer = 1.0f;
	const float maxShootingTimer = 5.0f;

	class Enemy : public Tank
	{
	private:
		float moveTimer;
		float shootingTimer;		
	public:
		Enemy(float xPosition, float yPosition, Vector2f size, Color color, const String imageFiles[maxTextures]);

		virtual void Update(Time dt, float xLimit, float yLimit);
		virtual void Shoot();
		virtual void MoveTank(Time dt);

		Direction GetRandomDirection();
		float GetRandomTimer(float min, float max);
	};
}

#endif
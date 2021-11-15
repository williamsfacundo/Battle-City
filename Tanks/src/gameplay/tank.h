#ifndef TANK_H
#define TANK_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "game_object.h"
#include "bullet.h"

using namespace sf;

namespace Battle_City
{
	enum class PlayerMovementSet { right, left, up, down, none };

	const float bulletsWidth = 15.0f;
	const float bulletsHeight = 15.0f;
	const short maxBullets = 10;	

	class Tank : public GameObject
	{
	protected:
		Vector2f size;
		RectangleShape rectangle;
		PlayerMovementSet moveStatus;
		Direction direction;
		Color color;
		GameObject* bullets[maxBullets];		
	public:
		Tank(float xPosition, float yPosition, Vector2f size, Color color);
		virtual ~Tank();

		void SetSize(float width, float heigth);
		Vector2f GetSize();
		
		virtual void Update(Time dt, float xLimit, float yLimit) = 0;
		virtual void Draw(RenderWindow& window);		

		void InitBullets();
		void DestroyBullet(short index);
		void DestroyBullets();
		short FindEmpyBulletIndex();
		virtual void Shoot() = 0;
		void MoveBullets(Time dt);
		void DrawBullets(RenderWindow& window);
		void DestroyBulletsOutOfMapLimits(float xLimit, float yLimit);		
	};
}

#endif

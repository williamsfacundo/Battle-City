#ifndef TANK_H
#define TANK_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/System/Time.hpp"

#include "game_object.h"
#include "bullet.h"

using namespace sf;

namespace Battle_City
{
	enum class PlayerMovementSet { right, left, up, down, none };
	const float tankMoveSpeed = 150.5f;
	const float timeBetweenShots = 0.65f;
	const float bulletsWidth = 15.0f;
	const float bulletsHeight = 15.0f;
	const short maxBullets = 10;
	const Color tankColor = Color::Green;
	const Keyboard::Key moveUp = Keyboard::Up;
	const Keyboard::Key moveDown = Keyboard::Down;
	const Keyboard::Key moveRight = Keyboard::Right;
	const Keyboard::Key moveLeft = Keyboard::Left;
	const Keyboard::Key shootKey = Keyboard::Space;

	class Tank : public GameObject
	{
	private:
		Vector2f size;
		RectangleShape rectangle;
		PlayerMovementSet moveStatus;
		Direction direction;
		GameObject* bullets[maxBullets];
		float shootingTimer;
	public:
		Tank(float xPosition, float yPosition, Vector2f size);
		~Tank();

		void SetSize(float width, float heigth);
		Vector2f GetSize();

		void Input();
		void Update(Time dt, float xLimit, float yLimit);
		virtual void Draw(RenderWindow& window);

		void MovementInput();
		void MovePlayer(Time dt);

		void InitBullets();
		void DestroyBullet(short index);
		void DestroyBullets();
		short FindEmpyBulletIndex();
		void Shoot();
		void MoveBullets(Time dt);
		void DrawBullets(RenderWindow& window);
		void DestroyBulletsOutOfMapLimits(float xLimit, float yLimit);

		void UpdateTimer(Time dt);
	};
}

#endif

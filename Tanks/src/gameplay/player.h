#ifndef PLAYER_H
#define PLAYER_H

#include "tank.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/String.hpp>

using namespace sf;

namespace Battle_City 
{
	enum class PlayerMovementSet { right, left, up, down, none };

	const float playerMoveSpeed = 150.5f;
	const float timeBetweenShots = 0.65f;

	const short initialLifes = 3;

	const Color playerTankColor = Color::Green;

	const Keyboard::Key moveUp = Keyboard::Up;
	const Keyboard::Key moveDown = Keyboard::Down;
	const Keyboard::Key moveRight = Keyboard::Right;
	const Keyboard::Key moveLeft = Keyboard::Left;
	const Keyboard::Key shootKey = Keyboard::Space;

	class Player : public Tank
	{
	private:
		PlayerMovementSet moveStatus;
		float shootingTimer;
		short lifes;		
	public:
		Player(float xPosition, float yPosition, Vector2f size, Color color, const String imageFiles[maxTextures]);
		~Player(); 		

		void DecreaseLifes();
		void setMoveStatus(PlayerMovementSet moveStatus);
		PlayerMovementSet GetMoveStatus();
		short GetLifes();
		 
		void Input();
		virtual void Update(Time dt, float xLimit, float yLimit);

		virtual void Shoot();
		void MovementInput();
		
		virtual void MoveTank(Time dt);		
	};
}

#endif

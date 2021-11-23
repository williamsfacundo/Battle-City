#ifndef PLAYER_H
#define PLAYER_H

#include "tank.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#include "global_vars.h"

using namespace sf;

namespace Battle_City 
{
	class Player : public Tank
	{
	private:		
		const float playerMoveSpeed = 150.5f;
		const float timeBetweenShots = 0.65f;
		
		const short initialLifes = 3;		

		PlayerMovementSet moveStatus;
		Keyboard::Key inputKeys[maxInputKeys];
		float shootingTimer;
		short lifes;		
	public:
		Player(float xPosition, float yPosition, Vector2f size, Color color, const String imageFiles[maxTextures], const Keyboard::Key inputKeys[maxInputKeys]);
		~Player(); 		

		void DecreaseLifes();
		void setMoveStatus(PlayerMovementSet moveStatus);
		PlayerMovementSet GetMoveStatus();
		short GetLifes();
		Keyboard::Key GetInputKeys(short index);
		 
		void Input();
		virtual void Update(Time dt, float xLimit, float yLimit);

		virtual void Shoot();
		void MovementInput();
		
		virtual void MoveTank(Time dt);

		bool IsTankMoving();
	};
}

#endif

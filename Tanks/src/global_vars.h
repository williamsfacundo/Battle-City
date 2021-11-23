#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

#include <SFML/Graphics/Color.hpp>

using namespace sf;

namespace Battle_City 
{
	//PLAYER
	const short maxInputKeys = 5;
	enum class PlayerMovementSet { right, left, up, down, none };
	const Color playerTankColor = Color::Green;

	//ENEMY
	const Color enemyTankColor = Color::Yellow;

	//GAME OBJECT
	enum class Direction { left, right, up, down };

	//TANK
	const short maxTextures = 8;
	enum class TextureType { left1, left2, right1, right2, up1, up2, down1, down2 };
	static const short maxBullets = 5;
}

#endif

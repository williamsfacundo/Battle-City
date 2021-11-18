#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "game_object.h"
#include "tank.h"
#include "player.h"

using namespace sf;

namespace Battle_City 
{	
	const String playerTexturesFiles[maxTextures] = {
		"assets/player/playerTankDownOne.png", "assets/player/playerTankDownTwo.png",
		"assets/player/playerTankLeftOne.png", "assets/player/playerTankLeftTwo.png",
		"assets/player/playerTankRightOne.png", "assets/player/playerTankRightTwo.png",
		"assets/player/playerTankUpOne.png", "assets/player/playerTankUpTwo.png" };

	const String enemyTexturesFiles[maxTextures] = {
		"assets/enemy/enemyTankDownOne.png", "assets/enemy/enemyTankDownTwo.png",
	 	"assets/enemy/enemyTankLeftOne.png", "assets/enemy/enemyTankLeftTwo.png",
		"assets/enemy/enemyTankRightOne.png", "assets/enemy/enemyTankRightTwo.png",
		"assets/enemy/enemyTankUpOne.png", "assets/enemy/enemyTankUpTwo.png" };

	const String nonDestroyableWallTextureFile = "assets/wall/nonDestroyableWall.png";
	const String destroyableWallTextureFile = "assets/wall/destroyableWall.png";
	const String mapLimitingWallFile = "assets/wall/mapLimitingWall.png";

	const Keyboard::Key playerOneInputKeys[maxInputKeys]{ Keyboard::Key::RControl, Keyboard::Key::Left, Keyboard::Key::Right, Keyboard::Key::Up, Keyboard::Key::Down};
	const Keyboard::Key playerTwoInputKeys[maxInputKeys]{ Keyboard::Key::LControl, Keyboard::Key::A, Keyboard::Key::D, Keyboard::Key::W, Keyboard::Key::S };
	const Keyboard::Key playerThreeInputKeys[maxInputKeys]{ Keyboard::Key::Space, Keyboard::Key::F, Keyboard::Key::H, Keyboard::Key::T, Keyboard::Key::G };
	const Keyboard::Key playerFourInputKeys[maxInputKeys]{ Keyboard::Key::P, Keyboard::Key::J, Keyboard::Key::L, Keyboard::Key::I, Keyboard::Key::K };

	const short maxEnemyTanks = 5;
	const short maxPlayers = 4;
	const short maxDestroyableWalls = 4;
	const short maxNonDestroyableWalls = 4;	
	const short maxMapLimitingWalls = 4;

	const float limitingWallXOffset = 125.0f;
	const float limitingWallYOffset = 100.0f;
	const float limitingWallWidth = 15.0f;
	const float limitingWallHeight = 15.0f;	

	class Gameplay
	{
	private:
		bool gameOver;
		short windowWidth;
		short windowHeigth;
		const char* title = "TANKS";
		RenderWindow window;
		GameObject* playerTank[maxPlayers];
		GameObject* enemyTank[maxEnemyTanks];
		GameObject* militaryBase;
		GameObject* destroyableWalls[maxDestroyableWalls];
		GameObject* nonDestroyableWalls[maxNonDestroyableWalls];
		GameObject* mapLimitingWalls[maxMapLimitingWalls];
		Clock clock;
		Time dt;		
	public:
		Gameplay(short numberOfPlayers);
		~Gameplay();

		void Input();
		void Update(Time dt);
		void Draw();
		void Run();

		void WinCondition();
		void DefeatCondition();		

		void EnemiesBulletsCollideWithPlayers();
		void DestroyEnemyTanksWhenHit();
		bool BulletsCollideWithMilitaryBase();
		void DestroyDestroyableWallsWhenHit();
		void DestroyBulletsWhenHitNonDestroyableWalls();
		void TanksCollideWithWalls();
		void TanksCollideWithMilitaryBase();
		void TanksCollideWithEachOther();
		bool AllTanksDestroyed();		
		void DestroyPlayerTankIfHasNoLifesLeft(short index);
	};
}

#endif

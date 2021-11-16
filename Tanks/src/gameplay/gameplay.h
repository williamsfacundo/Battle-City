#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/String.hpp>

#include "game_object.h"
#include "tank.h"

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

	const short maxEnemyTanks = 5;
	const short maxDestroyableWalls = 1;
	const short maxNonDestroyableWalls = 4;	

	class Gameplay
	{
	private:
		bool gameOver;
		short windowWidth;
		short windowHeigth;
		const char* title = "TANKS";
		RenderWindow window;
		GameObject* playerTank;
		GameObject* enemyTank[maxEnemyTanks];
		GameObject* militaryBase;
		GameObject* destroyableWalls[maxDestroyableWalls];
		GameObject* nonDestroyableWalls[maxNonDestroyableWalls];
		Clock clock;
		Time dt;
	public:
		Gameplay();
		~Gameplay();

		void Input();
		void Update(Time dt);
		void Draw();
		void Run();

		void WinCondition();
		void DefeatCondition();		

		bool EnemiesBulletsCollideWithPlayer();
		void DestroyEnemyTanksWhenHit();
		bool BulletsCollideWithMilitaryBase();
		void DestroyDestroyableWallsWhenHit();
		void DestroyBulletsWhenHitNonDestroyableWalls();
		void TanksCollideWithWalls();
		bool AllTanksDestroyed();		
	};
}

#endif

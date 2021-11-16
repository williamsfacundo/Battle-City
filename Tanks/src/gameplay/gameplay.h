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
	const short maxEnemyTanks = 5;
	const short maxDestroyableWalls = 4;
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
		bool AllTanksDestroyed();		
	};
}

#endif

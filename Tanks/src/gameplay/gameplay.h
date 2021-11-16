#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include "game_object.h"

using namespace sf;

namespace Battle_City 
{	
	const short maxEnemyTanks = 5;

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
		bool AllTanksDestroyed();
	};
}

#endif

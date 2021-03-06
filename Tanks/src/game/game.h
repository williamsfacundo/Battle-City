#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include "gameplay/gameplay.h"
#include "scene_manager.h"
#include "credits.h"
#include "menu.h"
#include "gameover.h"

namespace Battle_City 
{
	class Game
	{
	private:
		Clock clock;
		Time dt;
		RenderWindow window;		
		const char* title = "TANKS";
		short windowWidth;
		short windowHeigth;
		bool exit;	

		Gameplay* gameplay;
		SceneManager* sceneManager;
		Credits* credits;
		Menu* mainMenu;		
		GameOver* gameOver;
	public:
		Game();
		~Game();

		void Run();
	};
}

#endif
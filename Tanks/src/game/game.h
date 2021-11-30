#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>

#include "gameplay/gameplay.h"

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
	public:
		Game();
		~Game();

		void Run();
	};
}

#endif
#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Clock.hpp"

#include "game_object.h"

using namespace sf;

class Gameplay 
{
private:
	short windowWidth;
	short windowHeigth;
	const char* title = "TANKS";	
	RenderWindow window;	
	GameObject* playerTank;	
	Clock clock;
	Time dt;
public:
	Gameplay();
	~Gameplay();

	void Input();
	void Update(Time dt);
	void Draw();
	void Run();
};

#endif

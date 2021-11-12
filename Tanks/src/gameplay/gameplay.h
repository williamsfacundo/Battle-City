#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "SFML/Graphics/RenderWindow.hpp"

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
public:
	Gameplay();
	~Gameplay();

	void Input();
	void Update();
	void Draw();
	void Run();
};

#endif

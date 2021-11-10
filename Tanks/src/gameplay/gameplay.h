#ifndef gameplay_h
#define gameplay_h

#include "SFML/Graphics.hpp"

using namespace sf;

class Gameplay 
{
private:
	short windowWidth;
	short windowHeigth;
	const char* title = "TANKS";	
	RenderWindow window;
	CircleShape shape;
public:
	Gameplay();
	~Gameplay();

	void Input();
	void Update();
	void Draw();
	void Run();
};

#endif

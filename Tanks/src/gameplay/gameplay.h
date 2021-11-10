#ifndef gameplay_h
#define gameplay_h

#include "SFML/Graphics.hpp"

class Gameplay 
{
private:

public:
	Gameplay();
	~Gameplay();

	void Input();
	void Update();
	void Draw();
	void Run();
};

#endif

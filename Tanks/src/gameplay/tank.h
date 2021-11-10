#ifndef tank_h
#define tank_h

#include "game_object.h"

class Tank : public GameObject
{
private:

public:
	Tank(float xPosition, float yPosition);
	~Tank();
	
	void Input();
	void Update();
	virtual void Draw();
};

#endif

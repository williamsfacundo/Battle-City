#ifndef game_object_h
#define game_object_h

class GameObject 
{
private:
	float xPosition;
	float yPosition;
public:
	GameObject(float xPosition, float yPosition);	

	void SetPosition(float xPosition, float yPosition);
	float GetXPosition();
	float GetYPosition();
};

#endif

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics/RenderWindow.hpp>

using namespace sf;

namespace Battle_City 
{
	class GameObject
	{
	private:
		float xPosition;
		float yPosition;	
	protected:
		
	public:
		GameObject(float xPosition, float yPosition);
		virtual ~GameObject();

		void SetPosition(float xPosition, float yPosition);
		
		void AddXPosition(float value);
		void AddYPosition(float value);

		float GetXPosition();
		float GetYPosition();

		virtual void Draw(RenderWindow& window) = 0;		
	};
}

#endif

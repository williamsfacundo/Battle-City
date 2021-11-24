#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;

namespace Battle_City 
{
	class Rectangle
	{
	private:
		float xPosition;
		float yPosition;	
		Vector2f size;
	protected:
		
	public:
		Rectangle(float xPosition, float yPosition, Vector2f size);
		virtual ~Rectangle();
				
		void SetPosition(float xPosition, float yPosition);
		void SetSize(float width, float heigth);
		
		Vector2f GetSize();
		
		void AddXPosition(float value);
		void AddYPosition(float value);

		float GetXPosition();
		float GetYPosition();

		virtual void Draw(RenderWindow& window) = 0;		
	};
}

#endif

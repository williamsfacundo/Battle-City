#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "game_object.h"

namespace Battle_City 
{
	const Color baseColor = Color::White;

	class Base : public GameObject
	{
	private:
		Vector2f size;
		Color color; 
		RectangleShape rectangle;
	public:
		Base(float xPosition, float yPosition, Vector2f size);

		void SetSize(float width, float heigth);		
		Vector2f GetSize();	

		void Draw(RenderWindow& window);
	};
}

#endif

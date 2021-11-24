#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "rectangle.h"

namespace Battle_City 
{
	class Base : public Rectangle
	{
	private:
		const Color baseColor = Color::White;

		Vector2f size;
		Color color; 
		Texture baseTexture;
		Sprite baseSprite;
		RectangleShape rectangle;
	public:
		Base(float xPosition, float yPosition, Vector2f size);	

		void Draw(RenderWindow& window);
	};
}

#endif

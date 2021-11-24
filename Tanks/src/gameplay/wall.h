#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Color.hpp>

#include "rectangle.h"

namespace Battle_City 
{
	class Wall : public Rectangle
	{
	private:
		const Color destroyableWallColor = Color::Blue;
		const Color nonDestroyableWallColor = Color::Magenta;
		
		Color color;
		RectangleShape rectangle;
		Texture wallTexture;
		Sprite wallSprite;
		bool destroyable;
	public:
		Wall(float xPosition, float yPosition, Vector2f size, const String textureFile, bool destroyable);
		
		bool GetDestroyable();

		void Draw(RenderWindow& window);
	};
}

#endif

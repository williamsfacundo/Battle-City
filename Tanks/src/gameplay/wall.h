#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "game_object.h"

namespace Battle_City 
{

	const Color destroyableWallColor = Color::Blue;
	const Color nonDestroyableWallColor = Color::Magenta;

	class Wall : public GameObject
	{
	private:
		Vector2f size;
		Color color;
		RectangleShape rectangle;
		bool destroyable;
	public:
		Wall(float xPosition, float yPosition, Vector2f size, bool destroyable);

		void SetSize(float width, float heigth);
		Vector2f GetSize();
		bool GetDestroyable();

		void Draw(RenderWindow& window);
	};
}

#endif

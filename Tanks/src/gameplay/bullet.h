#ifndef BULLET_H
#define BULLET_H

#include "game_object.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#include "global_vars.h"

namespace Battle_City
{
	class Bullet : public GameObject
	{
	private:
		const float bulletMoveSpeed = 300.0f;
		const Color bulletColor = Color::Red;

		Vector2f size;
		RectangleShape rectangle;
		Direction direction;
		Texture bulletTexture;
		Sprite bulletSprite;
	public:
		Bullet(float xPosition, float yPosition, Vector2f size, Direction direction);

		void SetSize(float width, float heigth);
		void SetBulletSpriteDependingDirection(Direction direction);
		Vector2f GetSize();

		void Update(Time dt);
		virtual void Draw(RenderWindow& window);

		void MoveBullet(Time dt);

		bool BulletOutOfMapLimits(float xLimit, float yLimit);		
	};
}

#endif

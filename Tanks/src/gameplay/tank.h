#ifndef TANK_H
#define TANK_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>

#include "game_object.h"
#include "bullet.h"

using namespace sf;

namespace Battle_City
{
	const short maxTextures = 8;
	const float bulletsWidth = 15.0f;
	const float bulletsHeight = 15.0f;
	const short maxBullets = 5;	

	class Tank : public GameObject
	{
	private:
		Vector2f size;
		RectangleShape rectangle;		
		Direction direction;
		Color color;
		GameObject* bullets[maxBullets];
		String imageFiles[maxTextures];
		Texture tankTextures[maxTextures];
		Sprite tankSprite;
	public:
		Tank(float xPosition, float yPosition, Vector2f size, Color color, const String imageFiles[maxTextures]);
		virtual ~Tank();

		void SetSize(float width, float heigth);		
		void setDirection(Direction direction);
		void SetRectanglePosition(float xPos, float yPos);
		void SetSpritePosition(float xPos, float yPos);
		Vector2f GetSize();
		Direction getDirection();
		Vector2f getSize();		
		RectangleShape GetRectangle();
		
		virtual void Update(Time dt, float xLimit, float yLimit) = 0;
		virtual void Draw(RenderWindow& window);		

		void UpdateTimer(Time dt, float& timer);
		virtual void MoveTank(Time dt) = 0;

		void InitBullets();
		void DestroyBullet(short index);
		void DestroyBullets();
		short FindEmpyBulletIndex();
		virtual void Shoot() = 0;
		void MoveBullets(Time dt);
		void DrawBullets(RenderWindow& window);
		void DestroyBulletsOutOfMapLimits(float xLimit, float yLimit);		
		void CreateBullet(short index, float xPos, float yPos);
		GameObject* GetBullet(short index);
		bool IsBulletNull(short index);
	};
}

#endif

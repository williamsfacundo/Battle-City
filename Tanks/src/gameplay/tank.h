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
	enum class TextureType {left1, left2, right1, right2, up1, up2, down1, down2};

	const short maxTextures = 8;
	const float bulletsWidth = 15.0f;
	const float bulletsHeight = 15.0f;
	const short maxBullets = 5;	
	const float changeAnimationTime = 0.15f;

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
		TextureType textureType;
		float changeAnimationTimer;
		bool tankMoving;
		float moveSpeed;
	public:
		Tank(float xPosition, float yPosition, Vector2f size, Color color, const String imageFiles[maxTextures]);
		virtual ~Tank();

		void SetSize(float width, float heigth);		
		void setDirection(Direction direction);
		void SetRectanglePosition(float xPos, float yPos);
		void SetSpritePosition(float xPos, float yPos);
		void SetSpriteDependingDirection();
		void SetTankMoving(bool tankMoving);
		void SetMoveSpeed(float moveSpeed);
		void UpdateSpriteSize();		
		Vector2f GetSize();
		Direction getDirection();				
		RectangleShape GetRectangle();		
		bool GetTankMoving();
		float GetMoveSpeed();

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

		void Animation(Time dt);
		void SwitchBetweenTextures(TextureType type1, TextureType type2, short index1, short index2);
	};
}

#endif

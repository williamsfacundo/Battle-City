#include "tank.h"

#include <iostream>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/String.hpp>

#include "game_object.h"

namespace Battle_City
{
	Tank::Tank(float xPosition, float yPosition, Vector2f size, Color color, const String imageFiles[maxTextures]) : GameObject(xPosition, yPosition)
	{
		SetSize(size.x, size.y);
		rectangle.setSize(size);
		rectangle.setFillColor(color);
		SetRectanglePosition(xPosition, yPosition);
		direction = Direction::up;	
		textureType = TextureType::up1;
		float nextAnimation;

		InitBullets();

		for (short i = 0; i < maxTextures; i++)
		{
			this->imageFiles[i] = imageFiles[i];
		}

		for (short i = 0; i < maxTextures; i++)
		{
			tankTextures[i].loadFromFile(this->imageFiles[i]);		
		}		

		SetSpriteDependingDirection();

		UpdateSpriteSize();
		
		SetSpritePosition(GetXPosition(), GetYPosition());	
	}

	Tank::~Tank()
	{		
		DestroyBullets();
	}

	void Tank::SetSize(float width, float heigth)
	{
		size.x = width;
		size.y = heigth;
	}	

	void Tank::setDirection(Direction direction) 
	{
		this->direction = direction;		
	}

	void Tank::SetRectanglePosition(float xPos, float yPos) 
	{
		rectangle.setPosition(xPos, yPos);
	}

	void Tank::SetSpritePosition(float xPos, float yPos) 
	{
		tankSprite.setPosition(xPos, yPos);
	}

	void Tank::SetSpriteDependingDirection() 
	{
		switch (direction)
		{
		case Direction::left:

			tankSprite.setTexture(tankTextures[2]);
			textureType = TextureType::left1;			
			break;
		case Direction::right:
			tankSprite.setTexture(tankTextures[4]);
			textureType = TextureType::right1;
			break;
		case Direction::up:
			tankSprite.setTexture(tankTextures[6]);
			textureType = TextureType::up1;
			break;
		case Direction::down:
			tankSprite.setTexture(tankTextures[0]);
			textureType = TextureType::down1;
			break;
		default:

			break;
		}
	}	

	void Tank::UpdateSpriteSize() 
	{
		Vector2f actualSize;

		actualSize.x = tankSprite.getTextureRect().width;
		actualSize.y = tankSprite.getTextureRect().height;

		tankSprite.setScale(size.x / actualSize.x, size.y / actualSize.y);
	}

	Vector2f Tank::GetSize()
	{
		return size;
	}		

	Direction Tank::getDirection() 
	{
		return direction;
	}

	Vector2f Tank::getSize() 
	{
		return size;
	}	

	RectangleShape Tank::GetRectangle() 
	{
		return rectangle;
	}		

	void Tank::Draw(RenderWindow& window)
	{
#if _DEBUG
		window.draw(rectangle);
#endif		

		window.draw(tankSprite);

		DrawBullets(window);
	}

	void Tank::UpdateTimer(Time dt, float& timer) 
	{
		if (timer > 0.0f)
		{
			timer -= dt.asSeconds();
		}

		if (timer < 0.0f)
		{
			timer = 0.0f;
		}
	}

	void Tank::InitBullets()
	{
		for (short i = 0; i < maxBullets; i++)
		{
			bullets[i] = NULL;
		}
	}

	void Tank::DestroyBullet(short index)
	{
		if (bullets[index] != NULL)
		{
			delete bullets[index];
			bullets[index] = NULL;
		}
	}

	void Tank::DestroyBullets()
	{
		for (short i = 0; i < maxBullets; i++)
		{
			DestroyBullet(i);
		}
	}

	short Tank::FindEmpyBulletIndex()
	{
		short auxReturn = maxBullets;

		for (short i = 0; i < maxBullets; i++)
		{
			if (bullets[i] == NULL)
			{
				return i;
			}
		}

		return auxReturn;
	}	

	void Tank::MoveBullets(Time dt)
	{
		for (short i = 0; i < maxBullets; i++)
		{
			if (bullets[i] != NULL)
			{
				((Bullet*)bullets[i])->MoveBullet(dt);
			}
		}
	}

	void Tank::DrawBullets(RenderWindow& window)
	{
		for (short i = 0; i < maxBullets; i++)
		{
			if (bullets[i] != NULL)
			{
				((Bullet*)bullets[i])->Draw(window);
			}
		}
	}

	void Tank::DestroyBulletsOutOfMapLimits(float xLimit, float yLimit)
	{
		for (short i = 0; i < maxBullets; i++)
		{
			if (bullets[i] != NULL)
			{
				if (((Bullet*)bullets[i])->BulletOutOfMapLimits(xLimit, yLimit))
				{
					DestroyBullet(i);
				}
			}
		}
	}	

	void Tank::CreateBullet(short index, float xPos, float yPos) 
	{
		bullets[index] = new Bullet(xPos, yPos, { bulletsWidth, bulletsHeight }, getDirection());
	}

	GameObject* Tank::GetBullet(short index)
	{
		return bullets[index];
	}

	bool Tank::IsBulletNull(short index)
	{
		return bullets[index] == NULL;
	}

	void Tank::Animation(Time dt) 
	{
		UpdateTimer(dt, changeAnimationTimer);

		if (changeAnimationTimer == 0.0f)
		{
			switch (direction)
			{
			case Direction::left:		

				SwitchBetweenTextures(TextureType::left1, TextureType::left2, 2, 3);
				break;
			case Direction::right:

				SwitchBetweenTextures(TextureType::right1, TextureType::right2, 4, 5);
				break;
			case Direction::up:

				SwitchBetweenTextures(TextureType::up1, TextureType::up2, 6, 7);
				break;
			case Direction::down:

				SwitchBetweenTextures(TextureType::down1, TextureType::down2, 0, 1);
				break;			
			}

			changeAnimationTimer = changeAnimationTime;
		}		
	}

	void Tank::SwitchBetweenTextures(TextureType type1, TextureType type2, short index1, short index2)
	{
		if (textureType == type1)
		{
			tankSprite.setTexture(tankTextures[index1]);
			textureType = type2;
		}
		else
		{
			tankSprite.setTexture(tankTextures[index2]);
			textureType = type1;
		}

		UpdateSpriteSize();
	}
}

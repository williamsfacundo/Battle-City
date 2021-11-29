#include "base.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "rectangle.h"

namespace Battle_City
{
	Base::Base(float xPosition, float yPosition, Vector2f size) : Rectangle (xPosition, yPosition, size)
	{		
		rectangle.setSize(size);
		color = baseColor;
		rectangle.setFillColor(color);
		rectangle.setPosition(xPosition, yPosition);	

		baseTexture.loadFromFile("assets/MilitaryBase/baseSprite.png");
		baseSprite.setTexture(baseTexture);
		baseSprite.setPosition(xPosition, yPosition);

		Vector2f actualSize;

		actualSize.x = static_cast<float>(baseSprite.getTextureRect().width);
		actualSize.y = static_cast<float>(baseSprite.getTextureRect().height);

		baseSprite.setScale(size.x / actualSize.x, size.y / actualSize.y);
	}	

	void Base::Draw(RenderWindow& window) 
	{
#if _DEBUG
		window.draw(rectangle);
#endif

		window.draw(baseSprite);
		
	}
}
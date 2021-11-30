#include "credits.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "scene_manager.h"

using namespace sf;

namespace Battle_City 
{
	Credits::Credits(float windowWidth, float windowHeigth)
	{
		backgroundTexture.loadFromFile("assets/wallpapers/credits.png");
		
		backgroundSprite.setTexture(backgroundTexture);

		Vector2f actualSize;

		actualSize.x = static_cast<float>(backgroundSprite.getTextureRect().width);
		actualSize.y = static_cast<float>(backgroundSprite.getTextureRect().height);

		backgroundSprite.setScale(windowWidth / actualSize.x, windowHeigth / actualSize.y);
		backgroundSprite.setPosition(0.0f, 0.0f);		
	}

	void Credits::Input(SceneManager* sceneManager)
	{
		if (Keyboard::isKeyPressed(inputKey))
		{
			sceneManager->SetCurrentScene(inputChangeScene);
		}
	}

	void Credits::Draw(RenderWindow& window)
	{
		window.clear(Color::Black);

		window.draw(backgroundSprite);

		window.display();
	}
}
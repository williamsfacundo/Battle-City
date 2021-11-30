#include "menu.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace Battle_City 
{
	Menu::Menu(float windowWidth, float windowHeigth) 
	{
		actualButton = Buttons::pvscpu;	
		inputTimer = timeForInput;

		backgroundTexture.loadFromFile("assets/wallpapers/menu.png");
		tankTexture.loadFromFile("assets/player/playerOneTankDownOne.png");

		backgroundSprite.setTexture(backgroundTexture);
		tankSprite.setTexture(tankTexture);

		Vector2f actualSize;

		actualSize.x = static_cast<float>(backgroundSprite.getTextureRect().width);
		actualSize.y = static_cast<float>(backgroundSprite.getTextureRect().height);

		backgroundSprite.setScale(windowWidth / actualSize.x, windowHeigth / actualSize.y);
		backgroundSprite.setPosition(0.0f, 0.0f);

		actualSize.x = static_cast<float>(tankSprite.getTextureRect().width);
		actualSize.y = static_cast<float>(tankSprite.getTextureRect().height);

		tankSprite.setScale(tankSpriteSize.x / actualSize.x, tankSpriteSize.y / actualSize.y);
		tankSprite.setPosition(windowWidth / 2.0f - 140, windowHeigth / 2.0f + 70);
	}

	void Menu::Input(SceneManager* sceneManager, float windowWidth, float windowHeigth)
	{
		if (Keyboard::isKeyPressed(inputKeyUp) && inputTimer == 0.0f)
		{
			switch (actualButton)
			{
			case Buttons::pvscpu:

				actualButton = Buttons::exit;
				tankSprite.setPosition(windowWidth / 2.0f - 140.0f, windowHeigth / 2.0f + 70 + (tankSpriteMoveValue * 3));
				break;
			case Buttons::pvp:

				actualButton = Buttons::pvscpu;
				tankSprite.setPosition(windowWidth / 2.0f - 140.0f, windowHeigth / 2.0f + 70);
				break;
			case Buttons::credits:

				actualButton = Buttons::pvp;
				tankSprite.setPosition(windowWidth / 2.0f - 140.0f, windowHeigth / 2.0f + 70 + tankSpriteMoveValue);
				break;
			case Buttons::exit:

				actualButton = Buttons::credits;
				tankSprite.setPosition(windowWidth / 2.0f - 140.0f, windowHeigth / 2.0f + 70 + (tankSpriteMoveValue * 2));
				break;			
			}

			inputTimer = timeForInput;
		}
		else if (Keyboard::isKeyPressed(inputKeyDown) && inputTimer == 0.0f)
		{
			switch (actualButton)
			{
			case Buttons::pvscpu:

				actualButton = Buttons::pvp;
				tankSprite.setPosition(windowWidth / 2.0f - 140.0f, windowHeigth / 2.0f + 70 + tankSpriteMoveValue);
				break;
			case Buttons::pvp:

				actualButton = Buttons::credits;
				tankSprite.setPosition(windowWidth / 2.0f - 140.0f, windowHeigth / 2.0f + 70 + (tankSpriteMoveValue * 2));
				break;
			case Buttons::credits:

				actualButton = Buttons::exit;
				tankSprite.setPosition(windowWidth / 2.0f - 140.0f, windowHeigth / 2.0f + 70 + (tankSpriteMoveValue * 3));
				break;
			case Buttons::exit:

				actualButton = Buttons::pvscpu;
				tankSprite.setPosition(windowWidth / 2.0f - 140.0f, windowHeigth / 2.0f + 70);
				break;
			}

			inputTimer = timeForInput;
		}
		else if (Keyboard::isKeyPressed(inputKeySelect))
		{
			switch (actualButton)
			{
			case Buttons::pvscpu:
					
				sceneManager->SetCurrentScene(Scenes::pvscpu);
				break;
			case Buttons::pvp:
				
				sceneManager->SetCurrentScene(Scenes::pvp);
				break;
			case Buttons::credits:
								
				sceneManager->SetCurrentScene(Scenes::credits);
				break;
			case Buttons::exit:
								
				sceneManager->SetCurrentScene(Scenes::exit);
				break;
			}
		}
	}

	void Menu::Update(Time dt)
	{
		if (inputTimer > 0.0f) 
		{
			inputTimer -= dt.asSeconds();
		}
		else if (inputTimer < 0.0f)
		{
			inputTimer = 0.0f;
		}
	}

	void Menu::Draw(RenderWindow& window) 
	{
		window.clear(Color::Black);

		window.draw(backgroundSprite);
		window.draw(tankSprite);

		window.display();
	}
}
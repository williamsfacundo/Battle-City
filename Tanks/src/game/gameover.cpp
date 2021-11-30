#include "gameover.h"

namespace Battle_City 
{
	GameOver::GameOver(float windowWidth, float windowHeigth)
	{
		backgroundTexture.loadFromFile("assets/wallpapers/gameover.png");

		backgroundSprite.setTexture(backgroundTexture);

		Vector2f actualSize;

		actualSize.x = static_cast<float>(backgroundSprite.getTextureRect().width);
		actualSize.y = static_cast<float>(backgroundSprite.getTextureRect().height);

		backgroundSprite.setScale(windowWidth / actualSize.x, windowHeigth / actualSize.y);
		backgroundSprite.setPosition(0.0f, 0.0f);
	}

	void GameOver::Input(SceneManager* sceneManager)
	{
		if (Keyboard::isKeyPressed(inputKey))
		{
			sceneManager->SetCurrentScene(inputChangeScene);
		}
	}

	void GameOver::Draw(RenderWindow& window)
	{
		window.clear(Color::Black);

		window.draw(backgroundSprite);

		window.display();
	}
}
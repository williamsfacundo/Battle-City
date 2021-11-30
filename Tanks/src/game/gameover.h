#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "scene_manager.h"

using namespace sf;

namespace Battle_City 
{
	class GameOver
	{
	private:
		const Scenes inputChangeScene = Scenes::menu;
		const Keyboard::Key inputKey = Keyboard::Key::Enter;

		Texture backgroundTexture;
		Sprite backgroundSprite;
	public:
		GameOver(float windowWidth, float windowHeigth);

		void Input(SceneManager* sceneManager);
		void Draw(RenderWindow& window);
	};
}

#endif

#ifndef CREDITS_H
#define CREDITS_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "scene_manager.h"

using namespace sf;

namespace Battle_City 
{
	class Credits
	{
	private:
		const Scenes inputChangeScene = Scenes::pvp;
		const Keyboard::Key inputKey = Keyboard::Key::Enter;

		Texture backgroundTexture;
		Sprite backgroundSprite;
	public:
		Credits(float windowWidth, float windowHeigth);

		void Input(SceneManager* sceneManager);
		void Draw(RenderWindow& window);
	};
}

#endif

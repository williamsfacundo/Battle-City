#ifndef MENU_H
#define MENU_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

#include "scene_manager.h"

using namespace sf;

namespace Battle_City 
{
	enum class Buttons { pvscpu, pvp, credits, exit };

	class Menu
	{
	private:
		static const short maxButtons = 4;
		const Scenes inputChangeScenes[maxButtons] = { Scenes::pvscpu, Scenes::pvp, Scenes::credits, Scenes::exit };
		const Keyboard::Key inputKeyUp = Keyboard::Key::Up;
		const Keyboard::Key inputKeyDown = Keyboard::Key::Down;
		const Keyboard::Key inputKeySelect = Keyboard::Key::Space;
		const Vector2f tankSpriteSize = { 40.0f, 40.0f };
		const float tankSpriteMoveValue = 80.0f;
		const float timeForInput = 0.25f;

		Buttons actualButton;
		Texture backgroundTexture;
		Texture tankTexture;
		Sprite backgroundSprite;
		Sprite tankSprite;		
		float inputTimer;
	public:
		Menu(float windowWidth, float windowHeigth);

		void Input(SceneManager* sceneManager, float windowWidth, float windowHeigth);
		void Update(Time dt);
		void Draw(RenderWindow& window);
	};
}

#endif

#include "scene_manager.h"

namespace Battle_City
{
	SceneManager::SceneManager()
	{
		SetCurrentScene(initialScene);
	}

	void SceneManager::SetCurrentScene(Scenes currentScene)
	{
		this->currentScene = currentScene;
	}
	Scenes SceneManager::GetCurrentScene()
	{
		return currentScene;
	}
}

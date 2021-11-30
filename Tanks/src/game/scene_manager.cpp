#include "scene_manager.h"

namespace Battle_City
{
	SceneManager::SceneManager()
	{
		SetCurrentScene(initialScene);
		SetLastScene(initialScene);
	}

	void SceneManager::SetCurrentScene(Scenes currentScene)
	{
		this->currentScene = currentScene;
	}

	void SceneManager::SetLastScene(Scenes lastScene)
	{
		this->lastScene = lastScene;
	}
	
	Scenes SceneManager::GetCurrentScene()
	{
		return currentScene;
	}

	Scenes SceneManager::GetLastScene()
	{
		return lastScene;
	}
}

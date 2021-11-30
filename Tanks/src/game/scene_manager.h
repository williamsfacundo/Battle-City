#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

namespace Battle_City
{
	enum class Scenes { menu, credits, pvp, pvscpu, exit, endgame };
	
	class SceneManager
	{
	private:
		const Scenes initialScene = Scenes::menu;

		Scenes currentScene;
		Scenes lastScene;
	public:
		SceneManager();

		void SetCurrentScene(Scenes currentScene);
		void SetLastScene(Scenes lastScene);

		Scenes GetCurrentScene();
		Scenes GetLastScene();
	};
}

#endif


#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

namespace Battle_City
{
	enum class Scenes { menu, credits, pvp, pvscpu, exit };
	
	class SceneManager
	{
	private:
		const Scenes initialScene = Scenes::menu;

		Scenes currentScene;
	public:
		SceneManager();

		void SetCurrentScene(Scenes currentScene);
		Scenes GetCurrentScene();
	};
}

#endif


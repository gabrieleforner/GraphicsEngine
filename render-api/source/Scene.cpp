#include "util/Scene.h"

void SceneManager::loadScene(std::shared_ptr<Scene> scene)
{
	if (this->sceneInstance)
	{
		sceneInstance->onSceneExit();
	}
	sceneInstance = scene;
	if (this->sceneInstance)
	{
		sceneInstance->onSceneLoad();
	}
}

void SceneManager::update()
{
	if (sceneInstance)
	{
		sceneInstance->onSceneUpdate();
	}
}

void SceneManager::draw()
{
	if (sceneInstance)
	{
		sceneInstance->onSceneDraw();
	}
}

void SceneManager::cleanup()
{
	if (sceneInstance)
	{
		sceneInstance->onSceneExit();
	}
}

#include "util/Scene.h"

using namespace FastGFX::Util;

void SceneManager::loadScene(std::shared_ptr<Scene> scene)
{
	if (this->sceneInstance)
	{
		sceneInstance->onSceneExit(this->renderer);
	}
	sceneInstance = scene;
	if (this->sceneInstance)
	{
		sceneInstance->onSceneLoad(this->renderer);
	}
}

void SceneManager::update()
{
	if (sceneInstance)
	{
		sceneInstance->onSceneUpdate(this->renderer);
	}
}

void SceneManager::draw()
{
	if (sceneInstance)
	{
		sceneInstance->onSceneDraw(this->renderer);
	}
}

void SceneManager::cleanup()
{
	if (sceneInstance)
	{
		sceneInstance->onSceneExit(this->renderer);
	}
}

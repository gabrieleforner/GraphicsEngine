#include <util/Scene.h>

#include <iostream>

class SceneMain : public Scene
{
public:
	void onSceneLoad() override;
	void onSceneUpdate() override;
	void onSceneDraw() override;
	void onSceneExit() override;
};
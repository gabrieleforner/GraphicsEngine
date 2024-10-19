#ifndef __SCENE_H_
#define __SCENE_H_


#include <memory>
#include <util/ExportRule.h>

using namespace std;

class ENGINE_API Scene
{
public:
	virtual void onSceneLoad() = 0;
	virtual void onSceneUpdate() = 0;
	virtual void onSceneDraw() = 0;
	virtual void onSceneExit() = 0;
};

class ENGINE_API SceneManager
{
private:
	std::shared_ptr<Scene> sceneInstance;

public:
	void loadScene(std::shared_ptr<Scene> scene);
	void update();
	void draw();
	void cleanup();
};
#endif // !__SCENE_H_
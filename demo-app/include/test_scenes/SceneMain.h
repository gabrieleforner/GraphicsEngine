#include <util/Scene.h>

class SceneMain : public Scene
{
public:
	void onSceneLoad(Renderer renderer);
	void onSceneUpdate(Renderer renderer);
	void onSceneDraw(Renderer renderer);
	void onSceneExit(Renderer renderer);
};
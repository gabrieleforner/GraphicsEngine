#include <util/Scene.h>
#include <resource/Buffer.h>

using namespace FastGFX::Util;
using namespace FastGFX::Resource;

namespace GraphicsEngine {
	class SceneMain : public Scene
	{
	public:
		void onSceneLoad(Renderer renderer);
		void onSceneUpdate(Renderer renderer);
		void onSceneDraw(Renderer renderer);
		void onSceneExit(Renderer renderer);
	};
}
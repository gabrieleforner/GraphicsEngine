#pragma once
#include <memory>
#include <core/Renderer.h>

using namespace std;
using namespace FastGFX::Core;

namespace FastGFX::Util
{
	class Scene
	{
	public:
		virtual ~Scene() = default;
		virtual void onSceneLoad(Renderer renderer) = 0;
		virtual void onSceneUpdate(Renderer renderer) = 0;
		virtual void onSceneDraw(Renderer renderer) = 0;
		virtual void onSceneExit(Renderer renderer) = 0;
	};

	class SceneManager
	{
	private:
		std::shared_ptr<Scene> sceneInstance;

	public:
		Renderer renderer;
		void loadScene(std::shared_ptr<Scene> scene);
		void update();
		void draw();
		void cleanup();
	};
}
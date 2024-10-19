#include <iostream>
#include <core/AppModel.h>
#include <test_scenes/SceneMain.h>

class Gioco : public ApplicationModel
{
	void onApplicationStart()
	{
		scene_manager.loadScene(std::make_shared<SceneMain>());
		scene_manager.loadScene(std::make_shared<SceneMain>());
	}
};

AppConfig config{};

int main(int argc, char** argv)
{
	config.useEngineerMode = false;
	config.windowWidth = 800;
	config.windowHeight = 600;
	config.windowTitle = "PUERCO GOD";

	Gioco().Run(config);

	return 0;
}

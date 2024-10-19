#include <iostream>
#include <core/AppModel.h>
#include <test_scenes/SceneMain.h>

int main(int argc, char** argv)
{
	AppConfig config{};
	
	config.entryScene = std::make_shared<SceneMain>();
	config.useEngineerMode = false;
	config.windowWidth = 800;
	config.windowHeight = 600;
	config.windowTitle = "[FASTGFX] Gioco Godereccio v1.0-dev";

	ApplicationModel().Run(config);

	return 0;
}

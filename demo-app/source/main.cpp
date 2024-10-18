#include <iostream>
#include <core/AppModel.h>

class Gioco : public ApplicationModel
{
	//dio cnae
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

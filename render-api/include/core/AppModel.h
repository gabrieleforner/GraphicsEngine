#ifndef __APPMODEL_H_
#define __APPMODEL_H_

#include <iostream>
#include <stdexcept>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include "util/ExportRule.h"
#include "util/Scene.h"

// Sets base window settings (width, height, title)
struct ENGINE_API AppConfig
{
	int windowWidth;
	int windowHeight;
	std::string windowTitle;
	bool useEngineerMode;
	std::shared_ptr<Scene> entryScene;
};

class ENGINE_API ApplicationModel
{
protected:
	SceneManager scene_manager;
public:
	int Run(AppConfig config);
};
#endif
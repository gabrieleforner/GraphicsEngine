#pragma once

#include <iostream>
#include <GLFW/glfw3.h>
#include <core/Pipeline.h>

#include "util/Scene.h"

using namespace FastGFX::Util;
namespace FastGFX::Core
{
	// Sets base window settings (width, height, title)
	struct AppConfig
	{
		int windowWidth;
		int windowHeight;
		std::string windowTitle;
		bool useEngineerMode;
		std::shared_ptr<Scene> entryScene;
	};

class ApplicationModel
{
protected:
	SceneManager scene_manager;
public:
	int Run(AppConfig config);
};
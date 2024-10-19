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
};

class ENGINE_API ApplicationModel
{
protected:
	SceneManager scene_manager;
	virtual void onApplicationStart();	// Called at first frame.
	virtual void onApplicationUpdate();	// Non-drawing class and Mathematical Updates (e.g. setting BG color, updating Transforms)
	virtual void onApplicationDraw();	// Draw calls (e.g. drawing primitives)
	virtual void onApplicationExit();	// Clean up resources
public:
	int Run(AppConfig config);
};
#endif
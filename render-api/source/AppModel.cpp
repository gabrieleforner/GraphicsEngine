#include "core/AppModel.h"

int ApplicationModel::Run(AppConfig config)
{
	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(config.windowWidth, config.windowHeight, config.windowTitle.c_str(), NULL, NULL);
	if (window == NULL)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	Renderer renderer;
	std::cout << "=======================| FastGFX Engine |=======================" << std::endl;
	renderer.createInstance(config.useEngineerMode);

	scene_manager.renderer = renderer;
	scene_manager.loadScene(config.entryScene);
	while (!glfwWindowShouldClose(window))
	{
		scene_manager.update();
		scene_manager.draw();
		glfwPollEvents();
	}

	scene_manager.cleanup();
	renderer.destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
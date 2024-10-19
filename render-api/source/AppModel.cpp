#include "core/AppModel.h"

void ApplicationModel::onApplicationStart() {}
void ApplicationModel::onApplicationUpdate() {}
void ApplicationModel::onApplicationDraw() {}
void ApplicationModel::onApplicationExit() {}

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
	this->onApplicationStart();
	while (!glfwWindowShouldClose(window))
	{
		this->onApplicationUpdate();
		scene_manager.update();
		this->onApplicationDraw();
		scene_manager.draw();
		glfwPollEvents();
	}

	this->onApplicationExit();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
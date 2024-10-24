#include <test_scenes/SceneMain.h>

std::vector<Vertex> data_vector = {
	{{glm::vec3(1.0f, 1.0f, 1.0f)}, {glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}},
	{{glm::vec3(1.0f, 1.0f, 1.0f)}, {glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}},
	{{glm::vec3(1.0f, 1.0f, 1.0f)}, {glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)}}
};

VertexBuffer buffer{};

void SceneMain::onSceneLoad(Renderer renderer) {
	buffer.Create(renderer, data_vector);
}

	void SceneMain::onSceneUpdate(Renderer renderer) {

	}


void SceneMain::onSceneDraw(Renderer renderer) {
	renderer.clearBG(0.0f, 0.5f, 0.5f, 1.0f);
}

void SceneMain::onSceneExit(Renderer renderer) {

}





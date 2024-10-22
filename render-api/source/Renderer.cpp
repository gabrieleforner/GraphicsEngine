//
// Created by forner on 19/10/24.
//

#include "../include/core/Renderer.h"


void Renderer::createInstance() {
    std::cout << "Creating Renderer" << std::endl;
}

void Renderer::RenderGameObjects(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, std::vector<GameObject> gameObjects) {

	for (int i = 0; i < gameObjects.size(); i++)
	{
		PushData pushData;

		pushData.transform = gameObjects[i].transform.mat4();

		VkShaderStageFlags shaderStageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;

		//communicate with the shaders
		vkCmdPushConstants(commandBuffer, pipelineLayout, shaderStageFlags, 0, sizeof(pushData), &pushData);
	}

}
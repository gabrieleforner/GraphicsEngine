//
// Created by forner on 19/10/24.
//

#pragma once
#include <iostream>
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <..\..\demo-app\include\GameObject.h>

#include <vector>



class Renderer
{
public:
    VkInstance engine_instance;

    void createInstance();

    //keep a list of all gameobjects to render!!!
    void RenderGameObjects(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, std::vector<GameObject> gameObjects);
};



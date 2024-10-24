#include "resource/Buffer.h"

#include <util/ConsoleLog.h>

uint32_t findMemType(uint32_t typeFilter, VkPhysicalDevice pDevice, VkMemoryPropertyFlags memoryFlags)
{
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(pDevice, &memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & memoryFlags) == memoryFlags) {
            return i;
        }
    }

    printError("This machine cannot allocate!");
    exit(-1);
}

namespace FastGFX::Resource
{

    void VertexBuffer::Create(Core::Renderer render, std::vector<Vertex> bufferData)
    {
        VkBufferCreateInfo buffer_createInfo{};
        buffer_createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        buffer_createInfo.pNext = 0;
        buffer_createInfo.flags = 0;
        buffer_createInfo.size = sizeof(bufferData[0]) * bufferData.size();
        buffer_createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        buffer_createInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        vkCreateBuffer(render.engineDevice, &buffer_createInfo, nullptr, &this->vertexBufferObject);

        VkMemoryRequirements bufferMemoryRequirements;
        vkGetBufferMemoryRequirements(render.engineDevice, this->vertexBufferObject, &bufferMemoryRequirements);

        VkMemoryAllocateInfo allocateInfo{};
        allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocateInfo.pNext = 0;
        allocateInfo.allocationSize = bufferMemoryRequirements.size;
        allocateInfo.memoryTypeIndex = findMemType(bufferMemoryRequirements.memoryTypeBits, render.enginePhysicalDevice, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
        vkAllocateMemory(render.engineDevice, &allocateInfo, nullptr, &this->vertexBufferMemory);
        vkBindBufferMemory(render.engineDevice, this->vertexBufferObject, this->vertexBufferMemory, {0});

    }

    void VertexBuffer::Bind(Core::Renderer render)
    {
        VkDeviceSize offset = { 0 };
        vkCmdBindVertexBuffers(render.commandBuffer, 0, 1, &this->vertexBufferObject, &offset);
    }

    void VertexBuffer::Destroy(Core::Renderer renderer)
    {
        vkDestroyBuffer(renderer.engineDevice, this->vertexBufferObject, nullptr);
        vkFreeMemory(renderer.engineDevice, this->vertexBufferMemory, nullptr);
    }
}
#pragma once

#include <utility>
#include <vector>
#include <glm/glm.hpp>

#include "core/Renderer.h"

namespace  FastGFX::Resource
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec4 rgbaColor;
    };

    class VertexBuffer
    {
    private:
        VkBuffer vertexBufferObject = nullptr;
        VkDeviceMemory vertexBufferMemory = nullptr;

    public:
        // Fluid Methods
        void Create(Core::Renderer render, std::vector<Vertex> bufferData);
        void Bind(Core::Renderer render);
        void Destroy(Core::Renderer renderer);
    };
}

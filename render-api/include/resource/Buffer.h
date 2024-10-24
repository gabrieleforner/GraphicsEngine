#pragma once

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
    public:
        std::vector<Vertex> bufferData;
        void Create(Core::Renderer render);
        void Bind(Core::Renderer render);
        void Destroy(Core::Renderer renderer);
    };
}

//
// Created by Gabri on 24/10/2024.
//

#ifndef SHADER_H
#define SHADER_H

#include <vulkan/vulkan.h>
#include <util/ConsoleLog.h>
#include <core/Renderer.h>

#include "core/Renderer.h"

namespace FastGFX::Resource
{
    class Shader
    {
    private:
        Core::Renderer m_renderer;
    public:
        std::string fp_vertexShader;
        std::string fp_fragmentShader;

        void Create(Core::Renderer renderer);
        void Bind();
        void Destroy();
    };
}


#endif //SHADER_H

/*
 * Crunch Engine 3
 * Copyright 2026 Dodwell Industries
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef RENDERER3D_HPP
#define RENDERER3D_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <Crunch/core/renderer/Mesh.hpp>
#include <Crunch/core/renderer/Shader.hpp>
#include <Crunch/core/Camera.hpp>
#include <Crunch/core/renderer/Matrix/Matrix.hpp>

namespace Crunch {

class Renderer3D {
private:
public:
    bool Init(uint32_t vs, uint32_t fs);
    void Draw(Matrix::RenderList* list);

    unsigned int shaderProgram;
    unsigned int vertexShader;
    unsigned int fragmentShader;

    unsigned int viewLoc;
    unsigned int modlLoc;
    unsigned int projLoc;
};

}

#endif      // RENDERER3D_HPP

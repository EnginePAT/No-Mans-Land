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
#ifndef MESH_HPP
#define MESH_HPP

#include <Crunch/core/Texture.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <cstdint>

namespace Crunch {

struct Vertex {
    glm::vec3 position;             // Where is this in space?
    glm::vec4 color;                // RGBA color value
    glm::vec2 texCoord;             // Texture coordinate for texture mapping
    glm::vec3 normal;
};

class Mesh {
private:
    void Rebuild();
public:
    void SetPosition(glm::vec3 newPos);
    void SetScale(glm::vec3 newScale);
    void SetRotation(glm::vec3 newRot);
    void SetTexture(Texture* tex);

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    uint32_t icount;
    uint32_t vcount;

    Texture* m_Texture;
    glm::mat4 model;

    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;

    uint32_t id;
};

};

#endif      // MESH_HPP

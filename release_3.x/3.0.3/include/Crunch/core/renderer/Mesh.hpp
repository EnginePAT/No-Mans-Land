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
#include <Crunch/core/renderer/MeshRegistry.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <cstdint>

namespace Crunch {

struct Vertex {
    glm::vec3 position;             // Where is this in space?
    glm::vec4 color;                // RGBA color value
    glm::vec2 texCoord;             // Texture coordinate for texture mapping
};

class Mesh {
public:
    void create(std::vector<struct Vertex> verts, std::vector<uint32_t> idxs);
    void setTexture(Texture* tex, uint32_t prog);
    void setRotation(float degrees, glm::vec3 axis);
    void setPosition(glm::vec3 newPos);
    void setScale(glm::vec3 newScale);
    void resetModel();
    void updateBuffers(const std::vector<Vertex>& verts, const std::vector<uint32_t>& inds);

    std::vector<struct Vertex> vertices;
    std::vector<uint32_t> indices;
    uint32_t vcount;                // How many vertices in the vector
    uint32_t icount;                // How many indices in the vector

    uint32_t id;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    glm::mat4 model;

    glm::vec3 position;
};

};

#endif      // MESH_HPP

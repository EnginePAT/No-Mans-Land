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
#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <Crunch/core/renderer/Mesh.hpp>
#include <cstdint>
#include <vector>
#include <glm/glm.hpp>

namespace Crunch::Shapes {

class Quad {
public:
    Quad(float w, float h, glm::vec3 p, glm::vec4 c);

    float width;
    float height;
    glm::vec2 color;
    glm::vec3 position;
    glm::vec2 size;

    std::vector<struct Crunch::Vertex> vertices;
    std::vector<uint32_t> indices;
};

};

#endif      // SHAPES_HPP

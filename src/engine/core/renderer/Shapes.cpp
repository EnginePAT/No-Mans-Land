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
#include <Crunch/core/renderer/Shapes.hpp>

namespace Crunch::Shapes {

Quad::Quad(float w, float h, glm::vec3 p, glm::vec4 c) {
    color = c;
    width = w;
    height = h;

    size.x = width;
    size.y = height;

    position = p;
    float halfW = w / 2.0f;
    float halfH = h / 2.0f;

    // Create the vertices and push them into the vertices structure
    // Create the vertices centered around (0,0) locally using w and h
    // Top Right
    struct Crunch::Vertex v1 = { 
        glm::vec3( halfW,  halfH, 0.0f), 
        c, 
        glm::vec2(1.0f, 1.0f)
    };
    // Bottom Right
    struct Crunch::Vertex v2 = { 
        glm::vec3( halfW, -halfH, 0.0f), 
        c, 
        glm::vec2(1.0f, 0.0f)
    };
    // Bottom Left
    struct Crunch::Vertex v3 = { 
        glm::vec3(-halfW, -halfH, 0.0f), 
        c, 
        glm::vec2(0.0f, 0.0f)
    };
    // Top Left
    struct Crunch::Vertex v4 = { 
        glm::vec3(-halfW,  halfH, 0.0f), 
        c, 
        glm::vec2(0.0f, 1.0f)
    };
    vertices.push_back(v1);
    vertices.push_back(v2);
    vertices.push_back(v3);
    vertices.push_back(v4);

    // Add the indices
    // These are critical, because they define which vertex connects to each other
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);
}

}

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
#ifndef OPENGL_MESH_HPP
#define OPENGL_MESH_HPP

#include <cstdint>
#include <Crunch/core/renderer/Mesh.hpp>

namespace Crunch::BACKEND {

class OpenGL_Mesh {
public:
    void Create(Mesh* mesh);

    uint32_t id;
    uint32_t vao;
    uint32_t vbo;
    uint32_t ebo;
};

};

#endif      // OPENGL_MESH_HPP

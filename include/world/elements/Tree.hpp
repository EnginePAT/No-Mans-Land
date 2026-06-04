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
#ifndef TREE_HPP
#define TREE_HPP

#include <Crunch/core/renderer/Mesh.hpp>
#include <cstdint>
#include <vector>

namespace nml::WorldElements {

class Tree {
private:
    Crunch::Mesh mesh;
    std::vector<Crunch::Vertex> tmp_vertices;
    std::vector<uint32_t> tmp_indices;

public:
    void Create(glm::vec3 position);
    Crunch::Mesh GetMesh();
};

};

#endif      // TREE_HPP

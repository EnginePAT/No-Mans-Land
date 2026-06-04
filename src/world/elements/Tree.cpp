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
#include <iostream>
#include <world/elements/Tree.hpp>
#include <Crunch/core/renderer/Mesh.hpp>
#include <Crunch/core/renderer/Matrix/MatrixLoadModel.hpp>

namespace nml::WorldElements {

void Tree::Create(glm::vec3 position) {
    bool success;
    success = Crunch::Matrix::LoadModelData("assets/models/tree_pine.glb", tmp_vertices, tmp_indices);
    if (!success) {
        std::cout << "error: failed to load model!" << std::endl;
        return;
    }

    mesh.create(tmp_vertices, tmp_indices);
    mesh.resetModel();

    // Set the position and scale of the tree
    mesh.setPosition(position);
}

Crunch::Mesh Tree::GetMesh() {
    return mesh;
}

};

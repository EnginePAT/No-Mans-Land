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
#include "Crunch/core/backend/backend_context.hpp"
#include <Crunch/core/renderer/MeshRegistry.hpp>

namespace Crunch::Registry::MeshRegistry {

std::unordered_map<uint32_t, Mesh> meshes;
int id_index = 0;

void Set(uint32_t id, Mesh* mesh) {
    meshes[id_index++] = *mesh;
    BACKEND::RenderHandler::BackendSetMeshCache(mesh);
}

Mesh& Get(uint32_t id) {
    auto it = meshes.find(id);
    if (it != meshes.end()) {
        return it->second;
    }
    // Safe fallback or error log if Matrix requests a ghost ID
    throw std::runtime_error("MeshRegistry::Get(id) - Attempted to fetch non-existent mesh ID!");
}

bool Has(uint32_t id) {
    return meshes.find(id) != meshes.end();
}

};

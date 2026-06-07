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
#ifndef MESH_REGISTRY_HPP
#define MESH_REGISTRY_HPP

#include <Crunch/core/renderer/Mesh.hpp>
#include <cstdint>
#include <unordered_map>

namespace Crunch::Registry::MeshRegistry {

extern std::unordered_map<uint32_t, Mesh> meshes;

void Set(uint32_t id, Mesh* mesh);
Mesh& Get(uint32_t id);
bool Has(uint32_t id);

};

#endif      // MESH_REGISTRY_HPP

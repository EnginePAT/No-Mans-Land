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

#include <cstdint>
#include <vector>

namespace Crunch::Registry::MeshRegistry {

struct Mesh_GPU_Data {
    uint32_t id;
    uint32_t vao;
    uint32_t vbo;
    uint32_t ebo;

    uint32_t idx_count;         // Mesh specific indice count
    uint32_t vdx_count;         // Mesh specific vertex count
};

extern std::vector<struct Mesh_GPU_Data> mesh_data;
extern int mesh_data_count;

uint32_t resolveVAO(uint32_t id);
uint32_t resolveIDX(uint32_t id);
uint32_t appendToRegistry(uint32_t vao, uint32_t ebo, uint32_t vbo, uint32_t idx, uint32_t vdx);
void updateRegistryAtID(uint32_t id, uint32_t vao, uint32_t vbo, uint32_t ebo, uint32_t idx, uint32_t vdx);

};

#endif      // MESH_REGISTRY_HPP

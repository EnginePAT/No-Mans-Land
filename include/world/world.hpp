/*
 * No Mans Land
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
#ifndef WORLD_HPP
#define WORLD_HPP


#include "Crunch/core/Texture.hpp"
#include <cstdint>
#include <world/Terrain.hpp>
#include <Crunch/core/renderer/Mesh.hpp>
#include <vector>

namespace nml {         // nml = No Mans Land

constexpr float WORLD_SIZE = 256.0f;

class World {
private:
    uint32_t prog;
    Crunch::Texture pine_tree_trunk_tex;

public:
    void Init(uint32_t _prog);
    std::vector<Crunch::Mesh> Generate_World_Meshes();
    Terrain terrain;
};

}           // namespace nml


#endif      // WORLD_HPP

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
#include <Crunch/core/renderer/Mesh.hpp>
#include "world/Terrain.hpp"
#include <cstddef>
#include <random>
#include <world/world.hpp>

namespace nml {

std::vector<Crunch::Mesh> World::Generate_World_Meshes() {
    std::vector<Crunch::Mesh> meshes;

    std::vector<Crunch::Mesh> tmesh = terrain.Generate(SEED);
    for (const auto& mesh : tmesh) {
        meshes.push_back(mesh);
    }

    // Procedural tree generation goes here
    std::mt19937 rng(SEED);
    constexpr int TREE_COUNT = 500;

    std::uniform_real_distribution<float> xDist(-512.f, 512.f);
    std::uniform_real_distribution<float> zDist(-512.f, 512.f);
    std::uniform_real_distribution<float> sDist(0.8f, 1.4f);

    return meshes;
}

}

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
#include "Crunch/core/renderer/Matrix/Matrix.hpp"
#include <Crunch/core/renderer/Mesh.hpp>
#include <cstdint>
#include <stdexcept>
#include <world/Terrain.hpp>
#include <cstddef>
#include <world/World.hpp>
#include <FastNoiseLite.h>

namespace nml {

static FastNoiseLite tree_noise;

void World::Init(uint32_t _prog) {
    prog = _prog;

    terrain.Init(prog);

    if (!pine_tree_trunk_tex.load("assets/textures/pine_tree_trunk.jpg")) {
        throw std::runtime_error("error: could not load texture!");
    }
}

std::vector<Crunch::Mesh> World::Generate_World_Meshes() {
    std::vector<Crunch::Mesh> meshes;

    std::vector<Crunch::Mesh> tmesh = terrain.Generate(SEED);
    for (const auto& mesh : tmesh) {
        meshes.push_back(mesh);
    }

    // Procedural tree generation goes here
    tree_noise.SetSeed(SEED);
    tree_noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    tree_noise.SetFrequency(0.02f);     // Lower = bigger forests. Later this will be controlled by a biome system

    // Make the trees feel less "blobby"
    tree_noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    tree_noise.SetFractalOctaves(3);
    tree_noise.SetFractalGain(0.5f);

    constexpr int TREE_SAMPLES = 1000;

    for (int i = 0; i < TREE_SAMPLES; i++) {
        float x = tree_noise.GetNoise((float)i * 12.9898f, 78.233f);
        float z = tree_noise.GetNoise((float)i * 93.9898f, 12.233f);

        x = (x + 1.0f) * 0.5f * 256.0f;
        z = (z + 1.0f) * 0.5f * 256.0f;

        float density = tree_noise.GetNoise(x, z);

        float d = (density + 1.0f) * 0.5f;

        if (d < 0.55f) continue;        // No trees here

        float y = terrain.GetHeightAt({x, z});
        float eps = 0.5f;
        float hL = terrain.GetHeightAt({x - eps, z});
        float hR = terrain.GetHeightAt({x + eps, z});
        float hD = terrain.GetHeightAt({x, z - eps});
        float hU = terrain.GetHeightAt({x, z + eps});
        glm::vec3 n = glm::normalize(glm::vec3(
            hL - hR,
            hD - hU,
            2.0f * eps
        ));

        float slope = 1.0f - n.z; // rough slope metric
        if (slope > 0.35f) continue;

        float scale = 4.8f + (d * 3.8f);

        Crunch::Mesh& treeMesh = Crunch::Matrix::ModelCache::Get("tree_pine");
        Crunch::Mesh instance = treeMesh;
        instance.setPosition({x, y, z});
        instance.setScale(glm::vec3(scale));
        instance.setTexture(&pine_tree_trunk_tex, prog);
        meshes.push_back(instance);
    }

    return meshes;
}

}

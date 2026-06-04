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
#include <Crunch/Noise.hpp>
#include <FastNoiseLite.h>
#include <cstdint>

namespace Crunch::TerrainTools {

static FastNoiseLite noiseGenerator;

void InitializeNoise(uint32_t seed) {
    noiseGenerator.SetSeed(seed);
    noiseGenerator.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
}

float GenerateIndividualNoiseValue(uint32_t seed, float x, float y) {
    // Note: If you want to change seed per-call, you'd update it here, 
    // but usually, you set the seed once globally or per-chunk.
    
    // GetNoise returns a float between -1.0 and 1.0
    noiseGenerator.SetSeed(seed);
    return noiseGenerator.GetNoise(x, y);
}

}

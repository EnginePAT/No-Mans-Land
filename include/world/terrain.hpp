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
#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <cstdint>
#include <Crunch/core/renderer/Mesh.hpp>

namespace nml {

class Terrain {
private:
    uint32_t _prog;
public:
    void Init(uint32_t prog);
    std::vector<Crunch::Mesh> Generate(uint32_t seed);

    Crunch::Mesh mesh;
};

};          // namespace nml

#endif      // TERRAIN_HPP

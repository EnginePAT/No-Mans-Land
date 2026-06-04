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
#include <Crunch/core/renderer/Matrix/MatrixSubdivide.hpp>
#include <Crunch/core/renderer/Mesh.hpp>
#include <cstddef>
#include <cstdint>
#include <map>
#include <vector>

namespace Crunch::Matrix {

uint32_t GetMidpoint(uint32_t p1, uint32_t p2, std::vector<Crunch::Vertex>& vertices, std::map<int64_t, uint32_t>& cache) {
    // Create a unique 64-bit key for the edge between the two indices
    int64_t key = ((int64_t)std::min(p1, p2) << 32) | std::max(p1, p2);
    if (cache.count(key)) return cache[key];

    const auto& v1 = vertices[p1];
    const auto& v2 = vertices[p2];

    Crunch::Vertex midpoint;
    midpoint.position = (v1.position + v2.position) * 0.5f;
    midpoint.color    = (v1.color + v2.color) * 0.5f;
    midpoint.texCoord = (v1.texCoord + v2.texCoord) * 0.5f;

    vertices.push_back(midpoint);
    uint32_t index = vertices.size() - 1;
    cache[key] = index;
    return index;
}

void Subdivide(Mesh *mesh, int n) {
    // Subdivide the mesh pointer with n depth
    // If n = 0, then there are no subdivisions and no point wasting our time
    if (n <= 0) return;

    std::vector<Vertex> currentVerts = mesh->vertices;
    std::vector<uint32_t> currentIndices = mesh->indices;

    // Loop through each discrete level of subdivision depth
    for (int level = 0; level < n; ++level) {
        std::vector<uint32_t> nextIndices;
        std::map<int64_t, uint32_t> midpointCache;

        // Subdivide every single active triangle face group cleanly
        size_t totalIndices = currentIndices.size();
        for (size_t i = 0; i < totalIndices; i += 3) {
            uint32_t v1 = currentIndices[i];
            uint32_t v2 = currentIndices[i + 1];
            uint32_t v3 = currentIndices[i + 2];

            // Safely calculate or fetch shared midpoints
            uint32_t m1 = GetMidpoint(v1, v2, currentVerts, midpointCache);
            uint32_t m2 = GetMidpoint(v2, v3, currentVerts, midpointCache);
            uint32_t m3 = GetMidpoint(v3, v1, currentVerts, midpointCache);

            // Rebuild all 4 internal sub-triangles maintaining unified winding
            // Corner 1
            nextIndices.push_back(v1); nextIndices.push_back(m1); nextIndices.push_back(m3);
            // Corner 2
            nextIndices.push_back(m1); nextIndices.push_back(v2); nextIndices.push_back(m2);
            // Corner 3
            nextIndices.push_back(m3); nextIndices.push_back(m2); nextIndices.push_back(v3);
            // Center inverted face
            nextIndices.push_back(m1); nextIndices.push_back(m2); nextIndices.push_back(m3);
        }
        currentIndices = nextIndices;
    }

    // Re-upload the perfectly synchronized arrays back to Crunch Engine 3's core mesh handles
    // mesh->create(currentVerts, currentIndices);
    mesh->updateBuffers(currentVerts, currentIndices);
}

};

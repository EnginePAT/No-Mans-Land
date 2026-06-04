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
#include <cstdint>
#include <vector>
#include <world/Terrain.hpp>
#include <Crunch/core/renderer/Matrix/MatrixSubdivide.hpp>
#include <Crunch/core/renderer/Shapes.hpp>
#include <Crunch/core/renderer/Mesh.hpp>
#include <Crunch/Noise.hpp>
#include <glm/glm.hpp>

namespace nml {

// Tiny helper function to sample height consistently for our normal calculations
inline float GetHeightAt(uint32_t seed, float worldX, float worldZ) {
    constexpr float heightScale = 4.f;
    return heightScale * Crunch::TerrainTools::GenerateIndividualNoiseValue(seed, worldX, worldZ);
}

void DisplaceTerrainVertices(Crunch::Mesh& mesh, uint32_t seed) {
    // The gameplay code reads the engine's public translation states
    glm::vec3 chunkWorldPos = mesh.position;

    for (auto& vertex : mesh.vertices) {
        // Calculate continuous world space coordinates
        // Local Y maps to World Z due to the 90-degree X-rotation template
        float worldX = chunkWorldPos.x + vertex.position.x;
        float worldZ = chunkWorldPos.z + vertex.position.y;

        float y = GetHeightAt(seed, worldX, worldZ);
        vertex.position.z = y;

        constexpr float epsilon = 0.1f;
        float heightLeft  = GetHeightAt(seed, worldX - epsilon, worldZ);
        float heightRight = GetHeightAt(seed, worldX + epsilon, worldZ);
        float heightDown  = GetHeightAt(seed, worldX, worldZ - epsilon);
        float heightUp    = GetHeightAt(seed, worldX, worldZ + epsilon);

        glm::vec3 rawNormal;
        rawNormal.x = heightLeft - heightRight;
        rawNormal.y = heightDown - heightUp;
        rawNormal.z = 2.0f * epsilon; 

        vertex.normal = glm::normalize(rawNormal);

        // Simple height-based color mapping for a clean look
        float norm = (y + 5.0f) / 10.0f;
        vertex.color = glm::vec4(0.1f, norm * 0.6f + 0.2f, 0.1f, 1.0f);
    }
}

void Terrain::Init(uint32_t prog) {
    _prog = prog;
}

std::vector<Crunch::Mesh> Terrain::Generate(uint32_t _seed) {
    // Generate the terrain
    // We will use the Noise module from CE3 to generate a heightmap
    // Later, we will load 'assets/heightmaps/heightmap-*.chunk' and use that to determine the heights
    //  then use FastNoiseLite to fill in the gaps
    Crunch::Shapes::Quad quad(8.0f, 8.0f, glm::vec3(0), glm::vec4(1.0f));
    std::vector<Crunch::Mesh> meshes;
    seed = _seed;

    Crunch::Texture texture;
    if (!texture.load("assets/Ground.jpg")) {
        printf("failed to load texture\n");
    }

    for (float x = 0; x < 256.0f; x += 8.0f) {        // 16x16px chunk size
        for (float y = 0; y < 256.0f; y += 8.0f) {
            // 8x8 grid of "chunks" (64 total chunks)
            Crunch::Mesh mesh;
            mesh.create(quad.vertices, quad.indices);
            mesh.resetModel();
            mesh.setPosition(glm::vec3(x, 0.0f, y));
            mesh.setRotation(90.0f, glm::vec3(1.0f, 0, 0));
            mesh.setTexture(&texture, _prog);

            // Subdivide the mesh with a depth of 8 (Each quad gets subdivided 8 times)
            Crunch::Matrix::Subdivide(&mesh, 4);

            DisplaceTerrainVertices(mesh, seed);
            mesh.updateBuffers(mesh.vertices, mesh.indices);

            meshes.push_back(mesh);
        }
    }

    return meshes;
}

float Terrain::GetHeightAt(glm::vec2 position) {

    float height = nml::GetHeightAt(seed, position.x, position.y);
    return height;
}

}

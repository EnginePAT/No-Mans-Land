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
#include <Crunch/core/renderer/Matrix/MatrixLoadModel.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <cstdio>

namespace Crunch::Matrix {

// Recursive walker to traverse Assimp's node hierarchy and extract raw mesh blocks
void ProcessAssimpNode(aiNode* node, const aiScene* scene, std::vector<Crunch::Vertex>& vertices, std::vector<uint32_t>& indices) {
    for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        
        uint32_t vertexOffset = static_cast<uint32_t>(vertices.size());

        // 1. Pack mesh attributes straight into your native engine layout arrays
        vertices.reserve(vertices.size() + mesh->mNumVertices);
        for (unsigned int j = 0; j < mesh->mNumVertices; ++j) {
            Crunch::Vertex vertex;

            // Coordinates
            vertex.position.x = mesh->mVertices[j].x;
            vertex.position.y = mesh->mVertices[j].y;
            vertex.position.z = mesh->mVertices[j].z;

            // Baseline tint color (Solid white so it doesn't default to black in your fragment shaders)
            vertex.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

            // Texture Coordinates (Channel 0) mapped to your exact variable target
            if (mesh->mTextureCoords[0]) {
                vertex.texCoord.x = mesh->mTextureCoords[0][j].x;
                vertex.texCoord.y = mesh->mTextureCoords[0][j].y;
            } else {
                vertex.texCoord = glm::vec2(0.0f, 0.0f);
            }

            // Normals Extraction Pass
            if (mesh->HasNormals()) {
                vertex.normal.x = mesh->mNormals[j].x;
                vertex.normal.y = mesh->mNormals[j].y;
                vertex.normal.z = mesh->mNormals[j].z;
            } else {
                // Fallback orientation pointing straight up if the raw model asset lacks calculation vectors
                vertex.normal = glm::vec3(0.0f, 1.0f, 0.0f);
            }

            vertices.push_back(vertex);
        }

        // 2. Map Element Triangulation Indices
        for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
            aiFace face = mesh->mFaces[j];
            for (unsigned int k = 0; k < face.mNumIndices; ++k) {
                indices.push_back(vertexOffset + face.mIndices[k]);
            }
        }
    }

    // Drill down into child nodes (e.g., individual vehicle wheels, rifle attachments)
    for (unsigned int i = 0; i < node->mNumChildren; ++i) {
        ProcessAssimpNode(node->mChildren[i], scene, vertices, indices);
    }
}

bool LoadModelData(const std::string &path, std::vector<Crunch::Vertex> &outVertices, std::vector<uint32_t> &outIndices) {
    Assimp::Importer importer;

    // Fast-pipeline processing parameters tailored for raw OpenGL configurations
    const aiScene* scene = importer.ReadFile(path, 
        aiProcess_Triangulate |                // Force complex geometry into pristine triangles
        aiProcess_FlipUVs |                    // Inverts texture coords to match OpenGL coordinates
        aiProcess_GenSmoothNormals |           // Fallback generator for normal attributes
        aiProcess_JoinIdenticalVertices |      // Optimizes index structures heavily
        aiProcess_OptimizeMeshes               // Consolidates fragmented mesh components
    );

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::printf("[Matrix Error]: Assimp failed to load file -> %s. Reason: %s\n", path.c_str(), importer.GetErrorString());
        return false;
    }

    // Flush and reset memory layout states to prevent indexing errors
    outVertices.clear();
    outIndices.clear();

    // Start traversing the hardware asset tree from the root base node
    ProcessAssimpNode(scene->mRootNode, scene, outVertices, outIndices);

    std::printf("[Matrix HQ]: Successfully parsed model %s into Crunch::Vertex (%zu vertices, %zu indices)\n", 
                path.c_str(), outVertices.size(), outIndices.size());

    return true;
}

};

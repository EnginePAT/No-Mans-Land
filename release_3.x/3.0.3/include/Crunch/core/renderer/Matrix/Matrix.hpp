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
#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstdint>
#include <vector>
#include <glm/glm.hpp>
#include <Crunch/core/renderer/Mesh.hpp>

namespace Crunch::Matrix {

typedef struct {
    glm::mat4 model;
    uint32_t meshID;
    uint32_t materialID;
} DrawCommand;


// FrameData
// This structure gets passed onto the renderer
// The render backend has no idea about any camera matrices, since Matrix computes these
struct FrameData {
    glm::mat4 view;             // What is the camera looking at
    glm::mat4 projection;       // How are we looking at the view
};


// RenderList
// This is the list passed to the renderer so that it actually knows what to draw
// Includes a list of commands to execute, and a pointer 
//  to the FrameData so the GPU can actually make the user see something
struct RenderList {
    std::vector<DrawCommand> commands;          // Draw commands for the backend
    const struct FrameData* frame_data;
    int id_count;
};

RenderList Build(const std::vector<Mesh>& meshes, const FrameData* frame);

};

#endif      // MATRIX_HPP

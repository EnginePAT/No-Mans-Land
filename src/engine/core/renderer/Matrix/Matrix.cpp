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
#include <Crunch/core/renderer/Matrix/MatrixFrustumCulling.hpp>
#include <Crunch/core/renderer/Matrix/Matrix.hpp>

namespace Crunch::Matrix {

RenderList Build(const std::vector<Mesh>& meshes, const struct FrameData* frame) {
    RenderList list;
    list.id_count = 0;

    glm::mat4 viewProjection = frame->projection * frame->view;
    struct Frustum cameraFrustum = ExtractFrustum(viewProjection, 4.0f);

    for (const auto& mesh : meshes) {
        if (IsObjectInFrustum(&cameraFrustum, mesh.position, 16.0f)) {
            DrawCommand newCommand;
            newCommand.meshID = mesh.id;
            newCommand.materialID = 0;
            newCommand.model = mesh.model;                  // Crunch doesn't have support for Materials just yet

            list.commands.push_back(newCommand);
        }
    }

    list.frame_data = frame;
    return list;
}

}

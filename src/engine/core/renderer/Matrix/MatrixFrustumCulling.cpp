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

namespace Crunch::Matrix {

struct Frustum ExtractFrustum(const glm::mat4& vp, float chunk_pad) {
    Frustum frustum;

    // Left Plane
    frustum.planes[0].normal.x = vp[0][3] + vp[0][0];
    frustum.planes[0].normal.y = vp[1][3] + vp[1][0];
    frustum.planes[0].normal.z = vp[2][3] + vp[2][0];
    frustum.planes[0].distance = vp[3][3] + vp[3][0];

    // Right Plane
    frustum.planes[1].normal.x = vp[0][3] - vp[0][0];
    frustum.planes[1].normal.y = vp[1][3] - vp[1][0];
    frustum.planes[1].normal.z = vp[2][3] - vp[2][0];
    frustum.planes[1].distance = vp[3][3] - vp[3][0];

    // Bottom Plane
    frustum.planes[2].normal.x = vp[0][3] + vp[0][1];
    frustum.planes[2].normal.y = vp[1][3] + vp[1][1];
    frustum.planes[2].normal.z = vp[2][3] + vp[2][1];
    frustum.planes[2].distance = vp[3][3] + vp[3][1];

    // Top Plane
    frustum.planes[3].normal.x = vp[0][3] - vp[0][1];
    frustum.planes[3].normal.y = vp[1][3] - vp[1][1];
    frustum.planes[3].normal.z = vp[2][3] - vp[2][1];
    frustum.planes[3].distance = vp[3][3] - vp[3][1];

    // Near Plane
    frustum.planes[4].normal.x = vp[0][3] + vp[0][2];
    frustum.planes[4].normal.y = vp[1][3] + vp[1][2];
    frustum.planes[4].normal.z = vp[2][3] + vp[2][2];
    frustum.planes[4].distance = vp[3][3] + vp[3][2];

    // Far Plane
    frustum.planes[5].normal.x = vp[0][3] - vp[0][2];
    frustum.planes[5].normal.y = vp[1][3] - vp[1][2];
    frustum.planes[5].normal.z = vp[2][3] - vp[2][2];
    frustum.planes[5].distance = vp[3][3] - vp[3][2];

    // Normalize and extend frustum planes outwards
    for (int i = 0; i < 6; i++) {
        frustum.planes[i].Normalize();

        // Shift the frustum planes outwards to avoid clipping
        if (i < 4 && chunk_pad > 0.0f) {
            frustum.planes[i].distance += chunk_pad;
        }
    }

    return frustum;
}

bool IsObjectInFrustum(const Frustum *fr, const glm::vec3& pos, float size) {
    // Define the extents of our chunk's bounding box
    // Because of your 90-degree X-rotation, the chunk spans X and Z in world space
    glm::vec3 minBounds = glm::vec3(pos.x, -20.0f, pos.z);
    glm::vec3 maxBounds = glm::vec3(pos.x + size, 20.0f, pos.z + size);

    // Check against all 6 frustum planes
    for (int i = 0; i < 6; ++i) {
        const auto& plane = fr->planes[i];

        // Find the positive vertex of the bounding box along the plane normal
        glm::vec3 pVertex = minBounds;
        if (plane.normal.x >= 0) pVertex.x = maxBounds.x;
        if (plane.normal.y >= 0) pVertex.y = maxBounds.y;
        if (plane.normal.z >= 0) pVertex.z = maxBounds.z;

        // If the positive vertex is outside the plane, the entire box is culled
        if (glm::dot(plane.normal, pVertex) + plane.distance < 0) {
            return false; 
        }
    }
    return true;
}

};

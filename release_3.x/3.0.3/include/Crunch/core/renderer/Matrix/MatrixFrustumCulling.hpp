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
#ifndef FRUSTUM_CULLING_HPP
#define FRUSTUM_CULLING_HPP

#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include <glm/glm.hpp>

namespace Crunch::Matrix {

struct Plane {
    glm::vec3 normal;
    float distance;

    void Normalize() {
        float length = glm::length(normal);
        normal /= length;
        distance /= length;
    }
};

struct Frustum {
    // 6 planes
    // Near, far, left, right, top, bottom
    struct Plane planes[6];
};

struct Frustum ExtractFrustum(const glm::mat4& vp);
bool IsObjectInFrustum(const Frustum *fr, const glm::vec3& pos, float size);

}

#endif      // FRUSTUM_CULLING_HPP

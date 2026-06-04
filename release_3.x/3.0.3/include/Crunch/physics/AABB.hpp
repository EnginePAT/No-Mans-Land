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
#ifndef AABB_HPP
#define AABB_HPP

#include <glm/glm.hpp>

namespace Crunch::Physics {

typedef struct {
    glm::vec3 min;          // Bottom left corner
    glm::vec3 max;          // Top left corner
} AABB;

bool Intersects(const AABB& other);

}

#endif      // AABB_HPP

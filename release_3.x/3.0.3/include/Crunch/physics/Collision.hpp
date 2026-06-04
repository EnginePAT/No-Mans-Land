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
#ifndef COLLISION_HPP
#define COLLISION_HPP

#include <Crunch/physics/AABB.hpp>
#include <Crunch/physics/RigidBody.hpp>
#include <glm/glm.hpp>

namespace Crunch::Physics {

typedef struct CollisionInfo {
    bool intersected;
    glm::vec3 normal;
    float depth;
} CollisionInfo;

class CollisionHandler {
public:
    CollisionInfo GetAABBCollision(const AABB* a, const AABB* b);
    void ResolveCollision(RigidBody& a, RigidBody& b, const CollisionInfo& info);
};

};

#endif      // COLISION_HPP

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
#include <Crunch/physics/RigidBody.hpp>
#include <Crunch/physics/AABB.hpp>

namespace Crunch::Physics {

RigidBody::RigidBody() {
    position = glm::vec3(0.0f);
    velocity = glm::vec3(0.0f);
    acceleration = glm::vec3(0.0f);
    total_forces = glm::vec3(0.0f);

    mass = 1.0f;
    inv_mass = 1.0f;        // 1.0 / mass
    restitution = 0.4f;     // Bounciness (0.0 = mud, 1.0 = superball)
}

void RigidBody::ApplyForce(const glm::vec3& force) {
    total_forces += force;
}

AABB RigidBody::GetWorldAABB() const {
    return AABB { local_aabb.min, local_aabb.max + position };
}

}

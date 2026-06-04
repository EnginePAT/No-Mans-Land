/*
 * Crunch Engine 3
 * Copyright 2026 Dodwell Industries
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <Crunch/physics/Physics.hpp>
#include <Crunch/physics/RigidBody.hpp>
#include <Crunch/Noise.hpp>
#include <glm/glm.hpp>

namespace Crunch::Physics {

// Helper to grab height cleanly - Standard Positive Height Field
float GetTerrainHeight(uint32_t seed, float x, float z) {
    float heightScale = -4.f;
    return heightScale * Crunch::TerrainTools::GenerateIndividualNoiseValue(seed, x, z);
}

// Computes the exact surface normal of the terrain using a finite difference gradient
glm::vec3 GetTerrainNormal(uint32_t seed, float x, float z) {
    float epsilon = 0.05f; // Small offset step size
    
    float hL = GetTerrainHeight(seed, x - epsilon, z);
    float hR = GetTerrainHeight(seed, x + epsilon, z);
    float hB = GetTerrainHeight(seed, x, z - epsilon);
    float hF = GetTerrainHeight(seed, x, z + epsilon);
    
    // Create tangent vectors along X and Z axes based on height deltas
    glm::vec3 tangentX(epsilon * 2.0f, hR - hL, 0.0f);
    glm::vec3 tangentZ(0.0f, hF - hB, epsilon * 2.0f);
    
    // Standard Right-Hand Rule: crossing Z into X yields a clean UP (+Y) vector for positive heights
    float slopeX = hL - hR; 
    float slopeZ = hB - hF;
    
    return glm::normalize(glm::vec3(slopeX, epsilon * 2.0f, slopeZ));
    // return glm::normalize(glm::cross(tangentZ, tangentX));
}

void PhysicsHandler::UpdatePhysics(RigidBody* body, float dt, uint32_t seed) {
    if (body->inv_mass == 0.0f) return;

    // 1. Apply constant forces (Gravity - tuned for snappy simulation weight)
    glm::vec3 gravityForce = glm::vec3(0.0f, -24.5f, 0.0f) * body->mass;
    body->ApplyForce(gravityForce);

    // 2. F = ma -> Integrate velocity
    glm::vec3 acceleration = body->total_forces * body->inv_mass;
    body->velocity += acceleration * dt;

    // Terminal Velocity Clamp to guarantee zero chunk tunneling
    if (body->velocity.y < -60.0f) {
        body->velocity.y = -60.0f;
    }

    // Subtle Air Resistance on the horizontal plane
    body->velocity.x *= 0.80f;
    body->velocity.z *= 0.80f;

    // 3. Integrate position
    body->position += body->velocity * dt;

    // 4. --- TRUE PHYSICAL COLLISION RESPONSE ---
    float currentGroundHeight = GetTerrainHeight(seed, body->position.x, body->position.z);

    // Check if the body has breached the positive terrain surface
    if (body->position.y < currentGroundHeight) {
        glm::vec3 surfaceNormal = GetTerrainNormal(seed, body->position.x, body->position.z);

        // Solid surface locking - eliminates jitter and normal vector injection bugs
        body->position.y = currentGroundHeight;

        // Calculate relative velocity projected onto the slope normal
        float velAlongNormal = glm::dot(body->velocity, surfaceNormal);

        // Resolve kinetic impulse if the body is actively falling into the slope
        if (velAlongNormal < 0.0f) {
            float restitution = 0.0f; // Pure inelastic collision so walking down hills feels smooth
            float impulseScalar = -(1.0f + restitution) * velAlongNormal;
            impulseScalar /= body->inv_mass;

            // Apply normal impulse vector instantly
            body->velocity += body->inv_mass * impulseScalar * surfaceNormal;
        }

        // --- GROUND FRICTION DAEMON ---
        // Engages heavy braking if the surface normal indicates a walkable slope angle
        if (surfaceNormal.y > 0.7f) {
            body->velocity.x *= 0.75f; 
            body->velocity.z *= 0.75f; 
            
            // Clean cutoff to prevent floating-point creep down hills
            if (glm::length(glm::vec3(body->velocity.x, 0.f, body->velocity.z)) < 0.05f) {
                body->velocity.x = 0.0f;
                body->velocity.z = 0.0f;
            }
        }
    }

    // Reset forces accumulator for the next cycle
    body->total_forces = glm::vec3(0.0f);
}

}

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
#include "Crunch/core/Texture.hpp"
#include <Crunch/core/renderer/MeshRegistry.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Crunch/core/renderer/Mesh.hpp>
#include <cstddef>

namespace Crunch {

void Mesh::SetPosition(glm::vec3 newPos) {
    position = newPos;
    // Rebuild or update the model matrix
    Rebuild(); 
}

void Mesh::SetScale(glm::vec3 newScale) {
    scale = newScale;
    Rebuild();
}

void Mesh::SetRotation(glm::vec3 newRot) {
    rotation = newRot;
    Rebuild();
}

void Mesh::SetTexture(Texture* tex) {
    m_Texture = tex;
}

void Mesh::Rebuild() {
    model = glm::mat4(1.0f);        // Identity matrix. No transforms

    // Apply translation
    model = glm::translate(model, position);

    // Apply rotations (X, Y, then Z)
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // Apply scaling
    model = glm::scale(model, scale);
}

};

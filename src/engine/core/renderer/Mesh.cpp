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
#include <Crunch/core/renderer/MeshRegistry.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Crunch/core/renderer/Mesh.hpp>
#include <cstdint>
#include <vector>
#include <cstddef>

namespace Crunch {

void Mesh::create(std::vector<struct Vertex> verts, std::vector<uint32_t> idxs) {
    // Create the mesh here, and fill in the vertices and indices
    vertices = verts;
    indices = idxs;

    vcount = vertices.size();
    icount = indices.size();

    model = glm::mat4(1.0f);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    // Position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // Color attribute (location = 1)
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    // Texture attribute (location = 2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(2);

    // Normal attribute (location = 3)
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    id = Registry::MeshRegistry::appendToRegistry(VAO, EBO, VBO, icount, vcount);
}

void Mesh::setTexture(Texture* tex, uint32_t prog) {
    // glUniform1i(glGetUniformLocation(prog, "tex"), 0);
    // glActiveTexture(GL_TEXTURE0);
    // tex->bind();
    m_Texture = tex;
}

void Mesh::resetModel() {
    model = glm::mat4(1.0f);        // Identity matrix - no transforms
}

void Mesh::setRotation(float degrees, glm::vec3 axis) {
    model = glm::rotate(model, glm::radians(degrees), axis);
}

void Mesh::setPosition(glm::vec3 newPos) {
    // model = glm::mat4(1.0f);
    model = glm::translate(model, newPos);
    position = newPos;
}

void Mesh::setScale(glm::vec3 newScale) {
    model = glm::scale(model, newScale);
}

void Mesh::updateBuffers(const std::vector<Vertex>& verts, const std::vector<uint32_t>& inds) {
    this->vertices = verts;
    this->indices = inds;
    this->icount = inds.size();
    this->vcount = verts.size();

    // Re-bind the existing VAO/VBO/EBO handles and just push the new data size
    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    // Position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // Color attribute (location = 1)
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    // Texture attribute (location = 2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Update the MeshRegistry so Matrix knows that a change has occured
    // Without this, the renderer won't actually render anything
    Registry::MeshRegistry::updateRegistryAtID(id, this->VAO, this->VBO, this->EBO, this->icount, this->vcount);
}

};

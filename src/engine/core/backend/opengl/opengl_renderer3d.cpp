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
#include "Crunch/core/backend/opengl/opengl_mesh.hpp"
#include <Crunch/core/backend/opengl/opengl_renderer3d.hpp>
#include <Crunch/core/renderer/Matrix/Matrix.hpp>
#include <Crunch/core/renderer/MeshRegistry.hpp>
#include <Crunch/core/Window.hpp>
#include <Crunch/core/Camera.hpp>
#include <Crunch/core/renderer/Mesh.hpp>
#include <Crunch/core/renderer/Renderer3D.hpp>
#include <Crunch/core/renderer/Shader.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdint>
#include <iostream>

namespace Crunch::BACKEND {

bool OpenGL_Renderer3D::Init(uint32_t vs, uint32_t fs) {
    vertexShader = vs;
    fragmentShader = fs;

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char log[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, log);
        printf("shader link error: %s\n", log);
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    modlLoc = glGetUniformLocation(shaderProgram, "model");
    viewLoc = glGetUniformLocation(shaderProgram, "view");
    projLoc = glGetUniformLocation(shaderProgram, "projection");
    texLoc = glGetUniformLocation(shaderProgram, "tex");

    return true;
}

void OpenGL_Renderer3D::Draw(Matrix::RenderList* list) {
    glUseProgram(shaderProgram);

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(list->frame_data->view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(list->frame_data->projection));

    for (int i = 0; i < list->commands.size(); i++) {
        glUniformMatrix4fv(modlLoc, 1, GL_FALSE, glm::value_ptr(list->commands[i].model));
        
        uint32_t idx_count = Registry::MeshRegistry::Get(list->commands[i].meshID).icount;
        OpenGL_Mesh mesh = s_glMeshes[list->commands[i].meshID];
        uint32_t vao = mesh.vao;
        if (vao == 0) {
            // If resolveVAO returns 0, it means that the mesh with correct ID could not be found
            // Therefore an error needs to be thrown
            std::cout << "Invalid VAO!" << std::endl;
        }

        if (list->commands[i].texture != nullptr) {
            glActiveTexture(GL_TEXTURE0);
            list->commands[i].texture->bind();
            glUniform1i(texLoc, 0); // Point the sampler unit to GL_TEXTURE0
        }

        // glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, idx_count, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}

void OpenGL_Renderer3D::SetGLMesh(Mesh* mesh) {
    OpenGL_Mesh newMesh;
    newMesh.id = mesh->id;
    newMesh.Create(mesh);

    s_glMeshes[mesh->id] = newMesh;
}

};

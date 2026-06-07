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
#ifndef BACKEND_CONTEXT_HPP
#define BACKEND_CONTEXT_HPP

#include <glm/glm.hpp>
#include <Crunch/core/backend/opengl/opengl.hpp>

// Backend Types
// By default, this will be set to Vulkan, but can be changed at anytime
#define CRUNCH_BACKEND_OPENGL   0       // Legacy support. Doesn't have MDI.
#define CRUNCH_BACKEND_VULKAN   1       // Linux platforms
#define CRUNCH_BACKEND_METAL    2       // Apple platforms
#define CRUNCH_BACKEND_DIRECTX  3       // Windows platforms

namespace Crunch::BACKEND {

struct Backends {
    OpenGL_Backend opengl;
};

// This will be Vulkan for release
inline int backend = CRUNCH_BACKEND_OPENGL;
inline struct Backends backends;

bool Configure_Crunch_Backend(int type);
bool Initialize_Crunch_Backend();
void Terminate_Crunch_Backend();


/*
    Window Utilities to wrap the massive switch/case statements
*/
namespace WindowHandler {

bool BackendInit();
bool BackendCreate(int w, int h, const char* t);
bool BackendWindowShouldClose();
void BackendUpdate();
void BackendClear(glm::vec4 c);
void BackendTerminate();

GLFWwindow* BackendGetWindow();
float BackendGetDeltaTime();

}           // namespace WindowHandler


/*
    Renderer3D utilities to wrap the massive switch case/statements
*/
namespace RenderHandler {

// Renderer3D & Renderer2D functions go here
bool BackendInit(uint32_t vs, uint32_t fs);
void BackendDraw(Matrix::RenderList* list);
void BackendSetMeshCache(Mesh* mesh);

};          // namespace RenderHandler

}           // namespace Crunch::BACKEND::Handler

#endif      // BACKEND_CONTEXT_HPP

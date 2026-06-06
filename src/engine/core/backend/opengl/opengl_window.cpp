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
#include <cstddef>
#include <glad/glad.h>              // Very picky, needs to be included first
#include <Crunch/core/backend/opengl/opengl_window.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Crunch::BACKEND {

bool OpenGL_WINDOW::Init() {
    if (!glfwInit()) {
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif      // __APPLE__

    return true;
}

bool OpenGL_WINDOW::Create(int w, int h, const char* t) {
    _width = w;
    _height = h;
    _title = t;

    _window = glfwCreateWindow(_width, _height, _title, NULL, NULL);
    if (!_window) {
        return false;
    }
    glfwMakeContextCurrent(_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    lastTime = glfwGetTime();

    return true;
}

void OpenGL_WINDOW::Update() {
    glfwPollEvents();
    glfwSwapBuffers(_window);
}

void OpenGL_WINDOW::Clear(glm::vec4 c) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(c.x, c.y, c.z, c.w);
}

void OpenGL_WINDOW::Terminate() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

GLFWwindow* OpenGL_WINDOW::GetWindow() {
    return _window;
}

float OpenGL_WINDOW::GetDeltaTime() {
    float currentTime = glfwGetTime();
    float dt = currentTime -  lastTime;
    lastTime = currentTime;
    return dt;
}

}

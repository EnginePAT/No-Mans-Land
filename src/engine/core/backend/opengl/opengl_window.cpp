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
#include <iostream>

namespace Crunch::BACKEND {

bool OpenGL_WINDOW::Init() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "error: fatal: failed to initialize GLFW" << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /*
        Most system will work fine, but Apple depreciated OpenGL in 2019,
        so we enable forward compatibility to make sure it works properly without fault
    */
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif      // __APPLE__

    lastTime = glfwGetTime();

    return true;
}

bool OpenGL_WINDOW::Create(int w, int h, const char* t) {
    // Save the window details for later use
    _width = w;
    _height = h;
    _title = t;

    // Create the window & initialize GLAD
    _window = glfwCreateWindow(_width, _height, _title, NULL, NULL);
    if (!_window) {
        // The window is NULL, and an error occurred
        std::cout << "error: fatal: failed to create OpenGL window" << std::endl;
        return false;
    }
    glfwMakeContextCurrent(_window);        // Need to make the context current ready for GLAD

    // Initialize GLAD loader. This is essential for rendering
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // GLAD failed to load
        std::cout << "error: fatal: failed to load GLAD" << std::endl;
        return false;
    }

    // Enable Depth Testing. Required for 3D!
    glEnable(GL_DEPTH_TEST);

    // Set the framebuffer size callback
    // This function is called every time the window is resized
    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
    return true;
}

void OpenGL_WINDOW::Update() {
    // Poll events and swap the buffers
    glfwPollEvents();
    glfwSwapBuffers(_window);
}

void OpenGL_WINDOW::Clear(glm::vec4 c) {
    // Clear the screen to the color specified in the call
    // We clear the depth buffer as well, since depth testing is enabled
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(c.x, c.y, c.z, c.w);
}

bool OpenGL_WINDOW::WindowShouldClose() {
    // Should the window close or not?
    // This is used in the main loop, so that when the user clicks the close button, the application actually closes
    return glfwWindowShouldClose(_window);
}

void OpenGL_WINDOW::Terminate() {
    // Destroy the window, clean up, and destroy the OpenGL context
    glfwDestroyWindow(_window);
    glfwTerminate();
}

GLFWwindow* OpenGL_WINDOW::GetWindow() {
    // Just return the window type
    return _window;
}

float OpenGL_WINDOW::GetDeltaTime() {
    // Delta time is the difference in time between 2 frames
    // Helps us make movement and operations frame-independent
    //  because without it, faster computers will run the game faster!
    float currentTime = glfwGetTime();
    float dt = currentTime -  lastTime;
    lastTime = currentTime;
    return dt;
}

/*
    Private helper functions/callbacks
*/
void OpenGL_WINDOW::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

}

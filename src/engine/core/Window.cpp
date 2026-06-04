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
#include <Crunch/core/renderer/Shader.hpp>
#include <Crunch/core/Window.hpp>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>

namespace Crunch {

bool Window::init() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "error: fatal: failed to initialize GLFW" << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);      // OpenGL Version 4.1 Core

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

void Window::create(int w, int h, const char* title) {
    // Save the window details for later use
    _width = w;
    _height = h;
    _title = title;

    // Create the window & initialize GLAD
    _window = glfwCreateWindow(w, h, title, NULL, NULL);
    if (!_window) {
        // The window is NULL, and an error occurred
        std::cout << "error: fatal: failed to create OpenGL window" << std::endl;
        return;
    }
    glfwMakeContextCurrent(_window);                // Need to make the context current ready for GLAD

    // Initialize GLAD loader. This is essential for rendering
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // GLAD failed to load
        std::cout << "error: fatal: failed to load GLAD" << std::endl;
        return;
    }

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // Set the framebuffer size callback
    // This function is called every time the window is resized
    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);
}

bool Window::windowShouldClose() {
    // Should the window close or not?
    // This is used in the main loop, so that when the user clicks the close button, the application actually closes
    return glfwWindowShouldClose(_window);
}

void Window::update() {
    // Poll events and swap the buffers
    glfwPollEvents();
    glfwSwapBuffers(_window);
}

void Window::clear(glm::vec4 color) {
    // Clear the screen to the color specified in the call
    // We clear the depth buffer as well, since depth testing is enabled
    glClearColor(color.x, color.y, color.z, color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLFWwindow* Window::getWindow() {
    // Just return the window type
    return _window;
}

void Window::terminate() {
    // Destroy the window, clean up, and destroy the OpenGL context
    glfwDestroyWindow(_window);
    glfwTerminate();
}

float Window::getDeltaTime() {
    // Delta time is the difference in time between 2 frames
    // Helps us make movement and operations frame-independent
    //  because without it, faster computers will run the game faster!
    float currentTime = glfwGetTime();
    float dt = currentTime - lastTime;
    lastTime = currentTime;
    return dt;
}


/*
    Private helper functions/callbacks
*/
void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

}

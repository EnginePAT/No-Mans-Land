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
#include <Crunch/core/backend/backend_context.hpp>

namespace Crunch {

bool Window::init() {
    return BACKEND::WindowHandler::BackendInit();
}

void Window::create(int w, int h, const char* title) {
    _width = w;
    _height = h;
    _title = title;

    if (!BACKEND::WindowHandler::BackendCreate(w, h, title)) {
        std::cout << "Failed to create window!" << std::endl;
        return;
    }
}

bool Window::windowShouldClose() {
    // Should the window close or not?
    // This is used in the main loop, so that when the user clicks the close button, the application actually closes
    return BACKEND::WindowHandler::BackendWindowShouldClose();
}

void Window::update() {
    // Poll events and swap the buffers
    BACKEND::WindowHandler::BackendUpdate();
}

void Window::clear(glm::vec4 color) {
    // Clear the screen to the color specified in the call
    BACKEND::WindowHandler::BackendClear(color);
}

GLFWwindow* Window::getWindow() {
    // Just return the window type
    return BACKEND::WindowHandler::BackendGetWindow();
}

void Window::terminate() {
    // Destroy the window, clean up, and destroy the OpenGL context
    BACKEND::WindowHandler::BackendTerminate();
}

float Window::getDeltaTime() {
    // Delta time is the difference in time between 2 frames
    // Helps us make movement and operations frame-independent
    //  because without it, faster computers will run the game faster!
    return BACKEND::WindowHandler::BackendGetDeltaTime();
}


/*
    Private helper functions/callbacks
*/
void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

}

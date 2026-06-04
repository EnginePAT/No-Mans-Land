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
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Crunch {

class Window {
private:
    int _width;
    int _height;
    const char* _title;

    GLFWwindow* _window;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
public:
    bool init();
    void create(int w, int h, const char* title);
    bool windowShouldClose();
    void update();
    void clear(glm::vec4 color);
    void terminate();

    GLFWwindow* getWindow();
};

};

#endif      // WINDOW_HPP

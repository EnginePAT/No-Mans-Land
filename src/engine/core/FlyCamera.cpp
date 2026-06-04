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
#include <Crunch/core/FlyCamera.hpp>

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Crunch {

void FlyCamera::Init(Camera* cam, Window* win, float width, float height) {
    camera = cam;
    window = win;

    data.position = glm::vec3(0.0f, 2.0f, 3.0f);
    data.front = glm::vec3(0.0f, 0.0f, -1.0f);
    data.up = glm::vec3(0.0f, 1.0f, 0.0f);

    data.yaw = -90.0f;
    data.pitch = 0.0f;

    data.firstMouse = true;
    data.lastX = width * 0.5f;
    data.lastY = height * 0.5f;

    camera->cdata.view =
        glm::lookAt(data.position,
                    data.position + data.front,
                    data.up);

    glfwSetInputMode(window->getWindow(),
                     GLFW_CURSOR,
                     GLFW_CURSOR_DISABLED);

    glfwSetWindowUserPointer(window->getWindow(), this);

    glfwSetCursorPosCallback(
        window->getWindow(),
        [](GLFWwindow* w, double xpos, double ypos) {
            auto* cam =
                static_cast<FlyCamera*>(
                    glfwGetWindowUserPointer(w));

            if (cam)
                cam->mouseCallback(xpos, ypos);
        });
}

void FlyCamera::update(float dt, float speed) {
    glm::vec3 movement(0.0f);

    glm::vec3 right =
        glm::normalize(glm::cross(data.front, data.up));

    if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        movement += data.front;

    if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        movement -= data.front;

    if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        movement -= right;

    if (glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
        movement += right;

    if (glfwGetKey(window->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
        movement += data.up;

    if (glfwGetKey(window->getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        movement -= data.up;

    if (glm::length(movement) > 0.0f)
        movement = glm::normalize(movement);

    data.position += movement * speed * dt;

    camera->cdata.view =
        glm::lookAt(data.position,
                    data.position + data.front,
                    data.up);
}

void FlyCamera::mouseCallback(double xpos, double ypos) {
    if (data.firstMouse) {
        data.lastX = xpos;
        data.lastY = ypos;
        data.firstMouse = false;
    }

    float xoffset = xpos - data.lastX;
    float yoffset = data.lastY - ypos;

    data.lastX = xpos;
    data.lastY = ypos;

    const float sensitivity = 0.05f;

    xoffset *= sensitivity;
    yoffset *= sensitivity;

    data.yaw += xoffset;
    data.pitch += yoffset;

    if (data.pitch > 89.0f)
        data.pitch = 89.0f;

    if (data.pitch < -89.0f)
        data.pitch = -89.0f;

    glm::vec3 direction;

    direction.x =
        cos(glm::radians(data.yaw)) *
        cos(glm::radians(data.pitch));

    direction.y =
        sin(glm::radians(data.pitch));

    direction.z =
        sin(glm::radians(data.yaw)) *
        cos(glm::radians(data.pitch));

    data.front = glm::normalize(direction);
}

}

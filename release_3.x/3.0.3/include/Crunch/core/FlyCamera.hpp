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
#ifndef FLY_CAMERA_HPP
#define FLY_CAMERA_HPP

#include <Crunch/core/Camera.hpp>
#include <Crunch/core/Window.hpp>
#include <glm/glm.hpp>

namespace Crunch {

class FlyCamera {
public:
    FlyCamera(Camera* cam, Window* win, float width, float height);

    void update(float dt, float speed = 10.0f);

private:
    void mouseCallback(double xpos, double ypos);

    Camera* camera;
    Window* window;

    struct {
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;

        float yaw;
        float pitch;

        bool firstMouse;
        float lastX;
        float lastY;
    } data;
};

}

#endif

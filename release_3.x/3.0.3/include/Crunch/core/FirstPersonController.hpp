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
#ifndef FIRSTPERSONCONTROLLER_HPP
#define FIRSTPERSONCONTROLLER_HPP

#include <Crunch/core/Camera.hpp>
#include <Crunch/core/Window.hpp>
#include <Crunch/physics/RigidBody.hpp>
#include <glm/glm.hpp>

namespace Crunch {

class FirstPersonController {
private:
    struct KeyMap {
        int forward;            // Default configured to 'W' & 'UP'
        int backwards;          // Default configured to 'S' & 'DOWN'
        int left;               // Default configured to 'A' & 'LEFT'
        int right;              // Default configured to 'D' & 'RIGHT'
        int up;                 // Default configured to 'SPACE'
        int down;               // Default configured to 'LEFT SHIFT'
    };

    struct ControllerCoreData {
        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;

        glm::vec3 cameraTarget;
        glm::vec3 cameraDirection;
        glm::vec3 up;
        glm::vec3 cameraRight;

        glm::vec3 velocity;

        float yaw;
        float pitch;
        bool firstMouse;
        float lastX;
        float lastY;
    };

    Camera* camera;
    Window* window;

    struct AspectRatio {
        float x;
        float y;
    };
    struct AspectRatio aspect;

    float jumpForce = 50.f;

public:
    FirstPersonController(Camera* c, Window* w, float x, float y);
    void update(float dt, float speed);
    void mouseCallback(double xpos, double ypos);

    struct KeyMap keymap;       // This will hold the keymap for the controller
    struct ControllerCoreData coredata;
    bool isOnGround;
    Physics::RigidBody* body;
};

};

#endif          // FIRSTPERSONCONTROLLER_HPP

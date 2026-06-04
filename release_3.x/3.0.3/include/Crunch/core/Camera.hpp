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
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

#define CRUNCH_CAMERA_TYPE_PERSPECTIVE  0
#define CRUNCH_CAMERA_TYPE_ORTHO        1

namespace Crunch {

class Camera {
private:
    struct CameraData {
        glm::vec3 up;
        glm::vec3 forward;
        glm::vec3 position;

        float fovy;
        float aspect;
        float zNear;
        float zFar;

        glm::mat4 view;
        glm::mat4 projection;
    };
public:
    bool init(int type, float aspect, float fov, float zn, float zf);
    struct CameraData cdata;            // Camera data contains core camera vectors and the view/projection matrices
};

};

#endif      // CAMERA_HPP

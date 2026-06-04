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
#include <Crunch/core/Camera.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

namespace Crunch {

bool Camera::init(int type, float aspect, float fov, float zn, float zf) {
    cdata.aspect = aspect;
    cdata.fovy = fov;
    cdata.zNear = zn;
    cdata.zFar = zf;

    if (type == CRUNCH_CAMERA_TYPE_PERSPECTIVE) {
        // Use the perespective camera
        cdata.projection = glm::perspective(glm::radians(cdata.fovy), cdata.aspect, cdata.zNear, cdata.zFar);
    } else if (type == CRUNCH_CAMERA_TYPE_ORTHO) {
        // Use the orthographic camera
        std::cout << "warning: camera type not yet available: " << CRUNCH_CAMERA_TYPE_ORTHO << std::endl;
    } else {
        // The user specified an unavailable camera type
        std::cout << "warning: unknown camera type. some things may not render." << std::endl;
        return false;
    }

    cdata.view = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0), glm::vec3(0, 1.0f, 0));
    return true;
}

};

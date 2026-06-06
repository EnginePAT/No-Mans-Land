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
#include <Crunch/core/backend/backend_context.hpp>

namespace Crunch::BACKEND::WindowHandler {

bool BackendInit() {
    bool ret = false;

    switch (backend) {
        case CRUNCH_BACKEND_OPENGL: {
            ret = backends.opengl.window.Init();
            break;
        }

        default: {
            break;
        }
    }

    return ret;
}

bool BackendCreate(int w, int h, const char* t) {
    bool ret = false;

    switch (backend) {
        case CRUNCH_BACKEND_OPENGL: {
            ret = backends.opengl.window.Create(w, h, t);
            break;
        }

        default: {
            break;
        }
    }

    return ret;
}

bool BackendWindowShouldClose() {
    bool ret = false;

    switch (backend) {
        case CRUNCH_BACKEND_OPENGL: {
            ret = backends.opengl.window.WindowShouldClose();
            break;
        }

        default: {
            break;
        }
    }

    return ret;
}

void BackendUpdate() {
    switch (backend) {
        case CRUNCH_BACKEND_OPENGL: {
            backends.opengl.window.Update();
            break;
        }

        default: {
            break;
        }
    }
}

void BackendClear(glm::vec4 c) {
    switch (backend) {
        case CRUNCH_BACKEND_OPENGL: {
            backends.opengl.window.Clear(c);
            break;
        }

        default: {
            break;
        }
    }
}

void BackendTerminate() {
    switch (backend) {
        case CRUNCH_BACKEND_OPENGL: {
            backends.opengl.window.Terminate();
            break;
        }

        default: {
            break;
        }
    }
}

GLFWwindow* BackendGetWindow() {
    GLFWwindow* ret = nullptr;

    switch (backend) {
        case CRUNCH_BACKEND_OPENGL: {
            ret = backends.opengl.window.GetWindow();
            break;
        }

        default: {
            break;
        }
    }

    return ret;
}

float BackendGetDeltaTime() {
    float ret = 0.0f;

    switch (backend) {
        case CRUNCH_BACKEND_OPENGL: {
            ret = backends.opengl.window.GetDeltaTime();
            break;
        }

        default: {
            break;
        }
    }

    return ret;
}

}

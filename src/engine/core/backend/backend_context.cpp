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
#include <cstddef>

namespace Crunch::BACKEND {

bool Configure_Crunch_Backend(int type) {
    switch (type) {
        case CRUNCH_BACKEND_OPENGL: {
            // Use the OpenGL backend
            backend = CRUNCH_BACKEND_OPENGL;
            break;
        }
        case CRUNCH_BACKEND_VULKAN: {
            // Use the Vulkan backend
            backend = CRUNCH_BACKEND_VULKAN;
            break;
        }
        case CRUNCH_BACKEND_METAL: {
            // Use the Metal backend
            backend = CRUNCH_BACKEND_METAL;
            break;
        }
        case CRUNCH_BACKEND_DIRECTX: {
            // Use the Direct X 12 (DX12) backend
            backend = CRUNCH_BACKEND_DIRECTX;
            break;
        }
        default: {
            // Unknown
            break;
        }
    }

    return true;
}

bool Initialize_Crunch_Backend() {
    if (backend == CRUNCH_BACKEND_OPENGL) {
        backends.opengl.window.Init();
    } else if (backend == CRUNCH_BACKEND_METAL) {
        // backend = CRUNCH_BACKEND_METAL;
    } else if (backend == CRUNCH_BACKEND_VULKAN) {
        // backend = CRUNCH_BACKEND_VULKAN;
    } else if (backend == CRUNCH_BACKEND_DIRECTX) {
        // backend = CRUNCH_BACKEND_DIRECTX;
    } else {
        return false;
    }

    return true;
}

};

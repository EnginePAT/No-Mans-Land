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

namespace Crunch::BACKEND::RenderHandler {

bool BackendInit(uint32_t vs, uint32_t fs) {
    bool ret = false;

    switch (backend) {
        case CRUNCH_BACKEND_OPENGL: {
            ret = backends.opengl.renderer3d.Init(vs, fs);
            break;
        }

        default: {
            break;
        }
    }

    return ret;
}

void BackendDraw(Matrix::RenderList *list) {
    switch (backend) {
        case CRUNCH_BACKEND_OPENGL: {
            backends.opengl.renderer3d.Draw(list);
            break;
        }

        default: {
            break;
        }
    }
}

};

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
#ifndef BACKEND_CONTEXT_HPP
#define BACKEND_CONTEXT_HPP

// Backend Types
// By default, this will be set to Vulkan, but can be changed at anytime
#define CRUNCH_BACKEND_OPENGL   0       // Legacy support. Doesn't have MDI.
#define CRUNCH_BACKEND_VULKAN   1       // Linux platforms
#define CRUNCH_BACKEND_METAL    2       // Apple platforms
#define CRUNCH_BACKEND_DIRECTX  3       // Windows platforms

namespace Crunch::BACKEND::Handler {

// This will be Vulkan for release
inline int backend = CRUNCH_BACKEND_OPENGL;

bool Configure_Crunch_Backend(int type);
bool Initialize_Crunch_Backend();
void Terminate_Crunch_Backend();


}           // namespace Crunch::BACKEND::Handler

#endif      // BACKEND_CONTEXT_HPP

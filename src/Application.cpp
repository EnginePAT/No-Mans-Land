/*
 * No Mans Land
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
#include "Crunch/core/renderer/Matrix/Matrix.hpp"
#include "Crunch/core/renderer/Matrix/MatrixLoadModel.hpp"
#include "Crunch/core/renderer/Mesh.hpp"
#include <Application.hpp>
#include <cstdint>
#include <iostream>


namespace nml {

int NMLApp::Init() {

    bool init_status = window.init();
    if (!init_status) {
        std::cout << "error: failed to initialize Crunch Engine 3!" << std::endl;
    }
    window.create(WINDOW_WIDTH, WINDOW_HEIGHT, "No Mans Land");
    float aspect = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;


    // Shader setup
    const char* vss = loader.load("assets/vertex.glsl");
    const char* fss = loader.load("assets/fragment.glsl");
    uint32_t vs = loader.createShader(GL_VERTEX_SHADER, vss);
    uint32_t fs = loader.createShader(GL_FRAGMENT_SHADER, fss);

    // Crunch::Physics::RigidBody rb;

    
    renderer.Init(vs, fs);
    camera.init(CRUNCH_CAMERA_TYPE_PERSPECTIVE, aspect, 45.f, 0.01f, 1000.f);

    std::vector<Crunch::Vertex> vertices;
    std::vector<uint32_t> indices;
    Crunch::Matrix::LoadModelData("assets/models/tree_pine.glb", vertices, indices);
    Crunch::Mesh tree;
    tree.vertices = vertices;
    tree.indices = indices;
    Crunch::Matrix::ModelCache::Set("tree_pine", tree);

    world.Init(renderer.shaderProgram);
    std::vector<Crunch::Mesh> tmesh = world.Generate_World_Meshes();
    for (const auto& tm : tmesh) {
        meshes.push_back(tm);
    }

    fpc.Init(&camera, &window, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);
    // fly_cam.Init(&camera, &window, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);

    return 0;
}

void NMLApp::Run() {
    while (!window.windowShouldClose()) {
        float dt = window.getDeltaTime();

        fpc.update(dt, 15.f, 01234567);
        physics.UpdatePhysics(fpc.body, dt, 01234567);

        // Clear the screen to a nice color
        window.clear(glm::vec4(0));

        // Draw the mesh we created
        Crunch::Matrix::FrameData frame_data = { .projection=camera.cdata.projection, .view=camera.cdata.view };
        auto list = Crunch::Matrix::Build(meshes, &frame_data);
        renderer.Draw(&list);

        // Update the window (poll events and swap buffers)
        window.update();
    }
}

void NMLApp::Shutdown() {
    window.terminate();
}

}

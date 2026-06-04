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
#include <Crunch/Crunch.hpp>
#include <Crunch/core/Window.hpp>
#include <Crunch/core/renderer/Renderer3D.hpp>
#include <Crunch/core/renderer/Mesh.hpp>
#include <Crunch/core/renderer/Shader.hpp>
#include <Crunch/core/Camera.hpp>
#include <Crunch/core/renderer/Shapes.hpp>
#include <Crunch/core/FirstPersonController.hpp>
#include <Crunch/core/Texture.hpp>
#include <Crunch/physics/Physics.hpp>
#include <Crunch/physics/RigidBody.hpp>
#include <Crunch/core/renderer/Matrix/Matrix.hpp>
#include <Crunch/core/renderer/Matrix/MatrixSubdivide.hpp>
#include <Crunch/core/FlyCamera.hpp>
#include <Crunch/Noise.hpp>
#include <cstdint>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800

void DisplaceTerrainVertices(Crunch::Mesh& mesh, uint32_t seed) {
    // The gameplay code reads the engine's public translation states
    glm::vec3 chunkWorldPos = mesh.position;

    for (auto& vertex : mesh.vertices) {
        // Calculate continuous world space coordinates
        // Local Y maps to World Z due to the 90-degree X-rotation template
        float worldX = chunkWorldPos.x + vertex.position.x;
        float worldZ = chunkWorldPos.z + vertex.position.y;

        // Sample your gameplay noise function
        float height = 4.f;
        float y = height * Crunch::TerrainTools::GenerateIndividualNoiseValue(seed, worldX, worldZ);

        // Displace the vertex along its local perpendicular axis
        vertex.position.z = y;

        // Simple height-based color mapping for a clean look
        float norm = (y + 5.0f) / 10.0f;
        vertex.color = glm::vec4(0.1f, norm * 0.6f + 0.2f, 0.1f, 1.0f);
    }
}

int main() {
    Crunch::Window window;
    if (!window.init()) return -1;
    window.create(WINDOW_WIDTH, WINDOW_HEIGHT, "Crunch Engine Version 3 | Demo");

    float aspect = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;

    /* 
        Shader setup
        - We load the shader source into string
        - Then compile a shader object to pass to the renderer init
    */
    Crunch::Shader loader;
    const char* vss = loader.load("assets/vertex.glsl");
    const char* fss = loader.load("assets/fragment.glsl");
    uint32_t vs = loader.createShader(GL_VERTEX_SHADER, vss);
    uint32_t fs = loader.createShader(GL_FRAGMENT_SHADER, fss);

    /*
        Renderer
        The init call takes in the vertex and fragment shaders
        This lets the GPU know what to draw and how to draw it
    */
    Crunch::Renderer3D renderer;
    renderer.Init(vs, fs);

    /* Perspective camera setup. Note the CRUNCH_CAMERA_TYPE_PERSPECTIVE */
    Crunch::Camera camera;
    camera.init(CRUNCH_CAMERA_TYPE_PERSPECTIVE, aspect, 45.f, 0.01f, 1000.f);
    // Crunch::FirstPersonController fpc(&camera, &window, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);
    Crunch::FlyCamera fly_cam(&camera, &window, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);

    /* Sample mesh */
    Crunch::Texture texture;
    if (!texture.load("assets/Ground.jpg")) {
        printf("failed to load texture\n");
    }

    // Crunch::Physics::PhysicsHandler physics;
    // Crunch::Physics::RigidBody rb;

    Crunch::Shapes::Quad quad(8.0f, 8.0f, glm::vec3(0), glm::vec4(1.0f));
    std::vector<Crunch::Mesh> meshes;

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    for (float x = 0; x < 256.0f; x += 8.0f) {        // 16x16px chunk size
        for (float y = 0; y < 256.0f; y += 8.0f) {
            // 8x8 grid of "chunks" (64 total chunks)
            Crunch::Mesh mesh;
            mesh.create(quad.vertices, quad.indices);
            mesh.resetModel();
            mesh.setPosition(glm::vec3(x, 0.0f, y));
            mesh.setRotation(90.0f, glm::vec3(1.0f, 0, 0));
            mesh.setTexture(&texture, renderer.shaderProgram);

            // Subdivide the mesh with a depth of 8 (Each quad gets subdivided 8 times)
            Crunch::Matrix::Subdivide(&mesh, 4);

            DisplaceTerrainVertices(mesh, 01234567);
            mesh.updateBuffers(mesh.vertices, mesh.indices);

            meshes.push_back(mesh);
        }
    }

    /*
        Main game loop
        This is where the magic happens
        Generally it follows an order like this
            - Update
            - Clear
            - Render
    */
    float lastTime = glfwGetTime();
    while (!window.windowShouldClose()) {
        // Calculate delta time (∆T)
        // This is simple the difference between the current time and last time
        // Helps us to make movement or updates frame independant
        float currentTime = glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime;

        // fpc.update(dt, 7.5f);
        // physics.UpdatePhysics(fpc.body, dt);
        fly_cam.update(dt, 25.0f);

        // Clear the screen to a nice color
        window.clear(glm::vec4(0));

        // Draw the mesh we created
        Crunch::Matrix::FrameData frame_data = { .projection=camera.cdata.projection, .view=camera.cdata.view };
        auto list = Crunch::Matrix::Build(meshes, &frame_data);
        renderer.Draw(&list);

        // Update the window (poll events and swap buffers)
        window.update();
    }

    // Clean up and return
    window.terminate();
    return 0;
}

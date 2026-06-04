#include <Crunch/Crunch.hpp>
#include <Crunch/core/Window.hpp>
#include <Crunch/core/renderer/Renderer3D.hpp>
#include <Crunch/core/renderer/Mesh.hpp>
#include <Crunch/core/renderer/Shader.hpp>
#include <Crunch/core/Camera.hpp>
#include <Crunch/core/renderer/Shapes.hpp>
#include <Crunch/core/FirstPersonController.hpp>
#include <cstdint>

int main() {
    Crunch::Window window;
    if (!window.init()) return -1;
    window.create(800, 600, "Crunch Engine Version 3 | Demo");

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
    renderer.init(vs, fs);

    /* Perspective camera setup. Note the CRUNCH_CAMERA_TYPE_PERSPECTIVE */
    Crunch::Camera camera;
    camera.init(CRUNCH_CAMERA_TYPE_PERSPECTIVE, 800.f / 600.f, 45.f, 0.01f, 1000.f);
    Crunch::FirstPersonController fpc(&camera, &window);

    /* Sample mesh */
    Crunch::Mesh mesh;
    Crunch::Shapes::Quad ground_plane_data(1.f, 1.f, glm::vec3(0), glm::vec2(1.0f));
    mesh.create(ground_plane_data.vertices, ground_plane_data.indices, ground_plane_data.position, ground_plane_data.color);

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

        fpc.update(dt);

        // Clear the screen to a nice color
        window.clear(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

        // Draw the mesh we created
        renderer.draw(&mesh, &camera);

        // Update the window (poll events and swap buffers)
        window.update();
    }

    // Clean up and return
    window.terminate();
    return 0;
}

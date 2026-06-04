#ifndef APPLICATION_HPP
#define APPLICATION_HPP

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

#include <world/terrain.hpp>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800

namespace nml {

class NMLApp {
private:
    Crunch::Window window;
    Crunch::Shader loader;
    Crunch::Renderer3D renderer;
    Crunch::Camera camera;
    Crunch::Physics::PhysicsHandler physics;

    nml::Terrain terrain;
    // Crunch::FlyCamera fly_cam;
    Crunch::FirstPersonController fpc;
    std::vector<Crunch::Mesh> meshes;

public:
    int Init();
    void Run();
    void Shutdown();
};

}

#endif      // APPLICATION_HPP

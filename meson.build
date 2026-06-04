project('Crunch Engine 3', 'cpp', 'c',
    version: '3.0.1',
    default_options: [
        'cpp_std=c++17',
        'c_std=c11'
    ])

# Include folders
include_dir = include_directories('include')
glad_dir = include_directories('deps/glad/include/')
deps_dir= include_directories('deps/')

# Dependencies
glfw_dep = dependency('glfw3', required: true)
glm_dep = dependency('glm', required: true)
assimp_dep = dependency('assimp', required: true)

executable('no-mans-land',
    sources: [
        # CE3 (engine code)
        'src/engine/core/Window.cpp',
        'src/engine/core/renderer/Renderer3D.cpp',
        'src/engine/core/renderer/Mesh.cpp',
        'src/engine/core/renderer/Shader.cpp',
        'src/engine/core/renderer/Shapes.cpp',
        'src/engine/core/Camera.cpp',
        'src/engine/core/FirstPersonController.cpp',
        'src/engine/core/FlyCamera.cpp',
        'src/engine/core/Texture.cpp',
        'src/engine/core/renderer/MeshRegistry.cpp',
        'src/engine/Noise.cpp',

        'src/engine/core/renderer/Matrix/Matrix.cpp',
        'src/engine/core/renderer/Matrix/MatrixSubdivide.cpp',
        'src/engine/core/renderer/Matrix/MatrixFrustumCulling.cpp',
        'src/engine/core/renderer/Matrix/MatrixLoadModel.cpp',

        'src/engine/physics/RigidBody.cpp',
        'src/engine/physics/Physics.cpp',
        'src/engine/physics/Collision.cpp',


        # No Mans Land (game code)
        'src/main.cpp',
        'src/Application.cpp',
        'src/world/terrain.cpp',
        'src/Update.cpp',
        'src/Render.cpp',
        'src/world/elements/Tree.cpp',


        'deps/glad/src/glad.c',
    ],
    dependencies: [glfw_dep, glm_dep, assimp_dep],
    include_directories: [include_dir, glad_dir, deps_dir]
)

#ifndef RENDERER3D_HPP
#define RENDERER3D_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <Crunch/core/renderer/Mesh.hpp>
#include <Crunch/core/renderer/Shader.hpp>
#include <Crunch/core/Camera.hpp>

namespace Crunch {

class Renderer3D {
private:
public:
    bool init(uint32_t vs, uint32_t fs);
    void draw(Mesh* mesh, Camera* cam);

    unsigned int shaderProgram;
    unsigned int vertexShader;
    unsigned int fragmentShader;

    unsigned int viewLoc;
    unsigned int modlLoc;
    unsigned int projLoc;
};

}

#endif      // RENDERER3D_HPP

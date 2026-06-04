#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <cstdint>

namespace Crunch {

class Shader {
public:
    char* load(const char* path);
    char* tsrc;         // Temporary buffers to store shaders in. These get overwritten after each load call

    uint32_t createShader(GLenum type, const char* source);
};

};

#endif      // SHADER_HPP

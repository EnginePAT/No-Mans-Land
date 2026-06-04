#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <Crunch/core/renderer/Mesh.hpp>
#include <cstdint>
#include <vector>
#include <glm/glm.hpp>

namespace Crunch::Shapes {

class Quad {
public:
    Quad(float w, float h, glm::vec3 p, glm::vec2 c);

    float width;
    float height;
    glm::vec2 color;
    glm::vec3 position;
    glm::vec2 size;

    std::vector<struct Crunch::Vertex> vertices;
    std::vector<uint32_t> indices;
};

};

#endif      // SHAPES_HPP

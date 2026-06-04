#ifndef MESH_HPP
#define MESH_HPP

#include <glm/glm.hpp>
#include <vector>
#include <cstdint>

namespace Crunch {

struct Vertex {
    glm::vec3 position;
};

class Mesh {
private:
    unsigned int VBO;
    unsigned int EBO;
public:
    void create(std::vector<struct Vertex> verts, std::vector<uint32_t> idxs);

    std::vector<struct Vertex> vertices;
    std::vector<uint32_t> indices;
    uint32_t vcount;            // How many vertices in the vector
    uint32_t icount;            // How many indices in the vector

    unsigned int VAO;
    glm::mat4 model;
};

};

#endif      // MESH_HPP

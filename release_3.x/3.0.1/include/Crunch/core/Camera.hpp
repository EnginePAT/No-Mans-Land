#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

#define CRUNCH_CAMERA_TYPE_PERSPECTIVE  0
#define CRUNCH_CAMERA_TYPE_ORTHO        1

namespace Crunch {

class Camera {
public:
    bool init(int type);

    glm::mat4 view;
    glm::mat4 projection;
};

};

#endif      // CAMERA_HPP

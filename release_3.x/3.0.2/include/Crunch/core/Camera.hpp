#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

#define CRUNCH_CAMERA_TYPE_PERSPECTIVE  0
#define CRUNCH_CAMERA_TYPE_ORTHO        1

namespace Crunch {

class Camera {
private:
    struct CameraData {
        glm::vec3 up;
        glm::vec3 forward;
        glm::vec3 position;

        float fovy;
        float aspect;
        float zNear;
        float zFar;

        glm::mat4 view;
        glm::mat4 projection;
    };
public:
    bool init(int type, float aspect, float fov, float zn, float zf);
    struct CameraData cdata;            // Camera data contains core camera vectors and the view/projection matrices
};

};

#endif      // CAMERA_HPP

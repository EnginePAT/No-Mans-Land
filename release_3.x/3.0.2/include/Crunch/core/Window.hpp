#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Crunch {

class Window {
private:
    int _width;
    int _height;
    const char* _title;

    GLFWwindow* _window;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
public:
    bool init();
    void create(int w, int h, const char* title);
    bool windowShouldClose();
    void update();
    void clear(glm::vec4 color);
    void terminate();

    GLFWwindow* getWindow();
};

};

#endif      // WINDOW_HPP

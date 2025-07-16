#include "Window.h"
#include <iostream>
#include <ostream>
#include "GLFW/glfw3.h"

#define WINDOW_W 800
#define WINDOW_H 600

Window::Window() {
    window = nullptr;
}

Window::~Window() {
    Destroy();
}

bool Window::Initialize() {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_W, WINDOW_H, "OpenGL Graphics", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window); // A context being an object that holds whole of OpenGL

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    return true;
}

void Window::Destroy() {
    if (window != nullptr) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
}

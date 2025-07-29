#include "Window.h"
#include <iostream>
#include <glad/glad.h>
#include "GLFW/glfw3.h"

Window::Window() {
    window = nullptr;
}

Window::~Window() {

}

void Window::InitializeWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640,480, "Graphics", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0,0,640,480);
    ChangeColor(0.07f, 0.13f, 0.17f, window);
    RunWindow(window);

    glfwDestroyWindow(window);
}

void Window::ChangeColor(float Red, float Green, float Blue, GLFWwindow* Window) {
    glClearColor(Red, Green, Blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(Window);
}

void Window::RunWindow(GLFWwindow *Window) {
    while (!glfwWindowShouldClose(Window)) {
        glfwPollEvents();
    }
}

#include "Window.h"
#include <iostream>
#include <ostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Window::Window() {
    window = nullptr;
}

Window::~Window() {
    Destroy();
}

bool Window::Initialize() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    //Tell GLFW what version of OpenGL we are using
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //Tell GLFW we are using the CORE profile so we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window with the given resolution and title
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL Graphics", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    // Set the window into the current context
    glfwMakeContextCurrent(window); // A context being an object that holds whole of OpenGL

    // Load GLAD so it configures OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL from x=0, y=0 to maximum window width and height
    glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);

    // Specify the color of the background
    glClearColor(0.f, 0.f, 0.3f, 1.f);
    // Clean the back buffer and assign a new color to it
    glClear(GL_COLOR_BUFFER_BIT);
    // Swap the back buffer with the fron buffer so we see the color
    glfwSwapBuffers(window);

    glfwSetKeyCallback(window, KeyPressed);

    while (!glfwWindowShouldClose(window)) {
        // Take care of events (kind of event listener, example: key pressed, window resized)
        glfwPollEvents();
    }

    return true;
}

void Window::Destroy() {
    if (window != nullptr) {
        glfwDestroyWindow(window);
        window = nullptr;
        glfwTerminate();
    }
}

void Window::KeyPressed(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        printf("E key pressed\n");
    }
}

#include "Window.h"

#include <cmath>
#include <iostream>
#include <ostream>
#include "../Shader/Shader.h"
#include "../Shader/ElementBuffer/ElementBuffer.h"
#include "../Shader/VertexArray/VertexArray.h"
#include "../Shader/VertexBuffer/VertexBuffer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

GLfloat vertices[] =
    {
    -0.5f, -0.5f * static_cast<float>(std::sqrt(3.0)) / 3.0f, 0.0f, // Bottom-left
     0.5f, -0.5f * static_cast<float>(std::sqrt(3.0)) / 3.0f, 0.0f, // Bottom-right
     0.0f,  0.5f * static_cast<float>(std::sqrt(3.0)) * 2.0f / 3.0f, 0.0f, // Top-center
    -0.5f / 2, 0.5f * static_cast<float>(std::sqrt(3)) / 6, 0.f,
    0.5f / 2, 0.5f * static_cast<float>(std::sqrt(3)) / 6, 0.f,
    0.0f, -0.5f * static_cast<float>(std::sqrt(3)) / 3, 0.f,
};

GLuint indices[] =
    {
    0,3,5, // Lower left triangle
    3,2,4, // Lower Right
    5,4,1 // Upper
    };


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
    glfwSetWindowUserPointer(window, this);
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

    object.Initialize();

    Shader ShaderProgram("../Shader/default.vert", "../Shader/default.frag");
    VertexArray VAO;
    VAO.Bind();

    VertexBuffer VBO(vertices, sizeof(vertices));
    ElementBuffer EBO(indices, sizeof(indices));

    VAO.LinkVBO(VBO, 0);
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13, 0.17f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        ShaderProgram.Activate();
        VAO.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        // Take care of events (kind of event listener, example: key pressed, window resized)
        glfwPollEvents();
    }

    VAO.Delete();
    VBO.Delete();
    EBO.Delete();
    ShaderProgram.Delete();

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
    Window* Instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (!Instance) {
        printf("Error occured");
        return;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        Instance->object.SetTowardsDirection(true);
        Instance->object.MoveTowards();
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        Instance->object.SetTowardsDirection(false);
        Instance->object.MoveTowards();
    }
    if (key==GLFW_KEY_A && action == GLFW_PRESS) {
        Instance->object.SetLeftDirection(false);
        Instance->object.MoveLeft();
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        Instance->object.SetLeftDirection(true);
        Instance->object.MoveLeft();
    }
}

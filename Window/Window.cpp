#include "Window.h"
#include <iostream>
#include <random>
#include <thread>
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include<windows.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


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

    // leftmost part of the window is -1 and rightmost part of the window is 1
    // lowermost part of the window is -1 and topmost part of the window is 1
    // Normal floats may differ in size from GLFloat
    GLfloat vertices [] =
        {
        -0.5f, -0.5f * static_cast<float>(sqrt(3))      / 3, 0.f, // left corner
         0.5f, -0.5f * static_cast<float>(sqrt(3))      / 3, 0.f, // right corner
         0.0f,  0.5f * static_cast<float>(sqrt(3)) * 2  / 3, 0.f, // top
        };

    window = glfwCreateWindow(640,480, "Graphics", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0,0,640,480);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // first parameter is reference value, second the number of strings using for shader,
    // then we need the source code, last doesn't matter right now
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    // GPU can't understand source code so we have to compile it to machine code
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Need a shader program to wrap these shaders together

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    // We can delete the shader since it's already in the program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // VAO needs to be create before the VBO
    GLuint VAO; // Vertex Array Object stores pointers to VBOs so it can change between them and load them
    glGenVertexArrays(1, &VAO);

    // Create a vertex buffer object (not the same like with the frames)
    GLuint VBO; // it's an array of references but we only have one so we leave it like this
    glGenBuffers(1, &VBO); // we only have one references so we give 1 for the first parameter and then pointing it
    glBindVertexArray(VAO);
    // Make a certain object to the current object (binding) when we modify that kind of object it's going to
    // modify the current object aka the binded object
    glBindBuffer(GL_ARRAY_BUFFER, VBO); // Array buffer for the type we need to use for vertex buffer right now
    // Store our vertices in the VBO using glBufferData first specify type of buffer then giving actual data
    // 3 types of usages
    /*
     * STREAM: modified once and used a few times
     * STATIC: modified once and used a lot of times
     * DYNAMIC: modified multiple times and used multiple times
     */
    // There is DRAW, READ and COPY, Draw means it's going to be modified and used as an image on the screen
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Configure so OpenGl knows how to read the VBO
    // First index of VertexAttribute that's communicating with the Vertex Shader on the outside
    // How many values we have / vertex (we have 3 floates)
    // if we have our coordinates as integers
    // then the stride, we have 3 floates we're going to give the size of 3 floates
    // offset
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
    glEnableVertexAttribArray(0);

    // this is not mandatory but nice to have so we know we won't accidently change a VBO or VBA with a function
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //RunWindow(window);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // clean everything up when closing
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
}

void Window::ChangeColor(float Red, float Green, float Blue, GLFWwindow* Window) {
    glClearColor(Red, Green, Blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(Window);
}

void Window::RunWindow(GLFWwindow *Window) {
    float Angle = 0.0f;;
    float PrevTime = static_cast<float>(glfwGetTime());
    while (!glfwWindowShouldClose(Window)) {
        glfwPollEvents();
        float Time = static_cast<float>(glfwGetTime());
        if (Time - PrevTime >= 0.1f) {
            Angle += 0.1f;
            PrevTime = Time;
        }
        ChangeColor(static_cast<float>(sin(Angle)), static_cast<float>(cos(Angle)), static_cast<float>(tan(Angle)), window);
    }
}

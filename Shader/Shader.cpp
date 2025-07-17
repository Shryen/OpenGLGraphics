#include "Shader.h"
#include <cmath>
#include <fstream>

std::string Shader::get_file_contents(const char *FileName) {
    std::ifstream file(FileName, std::ios::in);
    if (file) {
        std::string contents;
        file.seekg(0, std::ios::end);
        contents.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&contents[0], contents.size());
        return contents;
    }
    throw(errno);
}

Shader::Shader(const char *VertexFile, const char *FragmentFile) {
    std::string vertexCode = get_file_contents(VertexFile);
    std::string fragmentCode = get_file_contents(FragmentFile);

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    // Create Vertex Shader Object and get reference
    GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(VertexShader, 1, &vertexSource, nullptr);
    // Compile the shader into machine code
    glCompileShader(VertexShader);

    // Create Fragment Shader Object and get reference
    GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach Fragment Shader source to the shader object
    glShaderSource(FragmentShader, 1, &fragmentSource, nullptr);
    // Compile shader into machine code
    glCompileShader(FragmentShader);

    //Create Shader program Object and get reference
    ID = glCreateProgram();
    // Attach shaders to the program
    glAttachShader(ID, VertexShader);
    glAttachShader(ID, FragmentShader);
    // Wrap-up/link all shaders together into the program
    glLinkProgram(ID);

    // Delete the now useless Vertex and Fragment objects
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

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

    GLuint VAO, VBO, EBO;
    // Generate VAO before VBO !!!IMPORTANT
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Shader::Activate() {
    glUseProgram(ID);
}

void Shader::Delete() {
    glDeleteProgram(ID);
}

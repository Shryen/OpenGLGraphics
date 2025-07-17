//
// Created by Krisz on 17/07/2025.
//

#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
#include "glad/glad.h"


class VertexBuffer {
public:
    GLuint ID;
    VertexBuffer(GLfloat* vertices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};



#endif //VERTEXBUFFER_H

//
// Created by Krisz on 17/07/2025.
//

#ifndef ELEMENTBUFFER_H
#define ELEMENTBUFFER_H
#include "glad/glad.h"


class ElementBuffer {
public:
    GLuint ID;
    ElementBuffer(GLuint* vertices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};


#endif //ELEMENTBUFFER_H

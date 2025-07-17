//
// Created by Krisz on 17/07/2025.
//

#include "VertexArray.h"
#include "../VertexBuffer/VertexBuffer.h"


VertexArray::VertexArray() {
    glGenVertexArrays(1, &ID);
}


void VertexArray::LinkVBO(VertexBuffer VBO, GLuint Layout) {
    VBO.Bind();
    glVertexAttribPointer(Layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(Layout);
    VBO.Unbind();
}

void VertexArray::Bind() {
    glBindVertexArray(ID);
}

void VertexArray::Unbind() {
    glBindVertexArray(0);
}

void VertexArray::Delete() {
    glDeleteVertexArrays(1, &ID);
}



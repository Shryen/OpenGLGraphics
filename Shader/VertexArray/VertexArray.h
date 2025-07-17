#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <glad/glad.h>

class VertexBuffer;

class VertexArray {
public:
    GLuint ID;
    VertexArray();

    void LinkVBO(VertexBuffer VBO, GLuint Layout);
    void Bind();
    void Unbind();
    void Delete();
};



#endif //VERTEXARRAY_H

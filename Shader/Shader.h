#ifndef SHADER_H
#define SHADER_H
#include <string>

#include "glad/glad.h"

class Shader {
public:
    std::string get_file_contents(const char* FileName);

    GLuint ID;
    Shader(const char* VertexFile, const char* FragmentFile);

    void Activate();
    void Delete();
};



#endif //SHADER_H

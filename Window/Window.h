#ifndef WINDOW_H
#define WINDOW_H
#include "GLFW/glfw3.h"


class Window {
public:
    Window();
    ~Window();

    bool Initialize();
    void Destroy();
private:
    GLFWwindow *window;
};



#endif //WINDOW_H

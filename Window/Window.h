#ifndef WINDOW_H
#define WINDOW_H
#pragma once

#include "../Object//Object.h"

class Object;
struct  GLFWwindow;

class Window {
public:
    Window();
    ~Window();

    bool Initialize();
    void Destroy();

private:
    GLFWwindow *window;
    Object object;

    static void KeyPressed(GLFWwindow *window, int key, int scancode, int action, int mods);
};

#endif //WINDOW_H

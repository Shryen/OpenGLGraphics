#ifndef WINDOW_H
#define WINDOW_H
#pragma once

struct  GLFWwindow;

class Window {
public:
    Window();
    ~Window();

    bool Initialize();
    void Destroy();
private:
    GLFWwindow *window;
};

#endif WINDOW_H

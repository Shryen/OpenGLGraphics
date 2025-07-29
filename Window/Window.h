#pragma once
#ifndef WINDOW_H
#define WINDOW_H

struct GLFWwindow;

class Window {
public:
    Window();
    ~Window();

    void InitializeWindow();
    GLFWwindow* GetWindow() const { return window; }

    void ChangeColor(float Red, float Green, float Blue, GLFWwindow* Window);

private:
    GLFWwindow* window;

    void RunWindow(GLFWwindow* Window);
};



#endif //WINDOW_H

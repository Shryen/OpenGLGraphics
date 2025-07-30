#include <GLFW/glfw3.h>
#include "Window/Window.h"


int main() {
    Window* CurrentWindow = new Window();
    CurrentWindow->InitializeWindow();
    glfwTerminate();
    return 0;
}

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window/Window.h"

int main() {
    Window Window;
    if (!Window.Initialize()) {
        std::cerr << "Failed to initialize window" << std::endl;
        return -1;
    }
    return 0;
}

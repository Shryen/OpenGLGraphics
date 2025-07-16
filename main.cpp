#include <iostream>
#include "Window/Window.h"

int main() {
    Window Window;
    if (!Window.Initialize()) {
        std::cerr << "Failed to initialize window" << std::endl;
        return -1;
    }
    Window.Destroy();
    return 0;
}

cmake_minimum_required(VERSION 3.10)
project(OpenGLGraphics CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.cpp
        glad.c
        Window/Window.cpp
        Window/Window.h
)

set(LIBRARIES_DIR "${CMAKE_SOURCE_DIR}/Libraries")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC
        ${LIBRARIES_DIR}/include)

target_link_libraries(${PROJECT_NAME}
        gdi32          # For Windows GDI functions
        opengl32       # For OpenGL rendering context
        winmm          # Windows Multimedia (often for input, joysticks, timers)
        kernel32       # Core Windows API functions
        user32         # User Interface API functions
        shell32        # Windows Shell API functions
        # --- Move libglfw3.a to the end ---
        ${LIBRARIES_DIR}/lib/libglfw3.a
)
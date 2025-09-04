# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(OpenGLApp)

# Find the necessary packages
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Add your executable target
# Include glad.c here so CMake compiles it along with main.cpp
add_executable(OpenGLApp src/main.cpp src/glad.c)

# Tell the project where to find header files (for GLAD)
target_include_directories(OpenGLApp PUBLIC include)

# Link the required libraries to your executable
target_link_libraries(OpenGLApp
    glfw
    ${OpenGL_LIBRARIES}
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreFoundation"
)
# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(OpenGLApp)

# Specify the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add a user-configurable option to enable sandbox mode (default is OFF)
option(ENABLE_SANDBOX "Enable the sandbox preprocessor definition" OFF)

# Find necessary packages for OpenGL and windowing
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)



  set(IMGUI_PATH include/imgui)
file(GLOB IMGUI_SOURCES "${IMGUI_PATH}/*.cpp")

# Define the executable target with ALL its source files
add_executable(OpenGLApp
    src/main.cpp
    src/glad.c
    src/RayTracing.cpp
    src/basics.cpp
    ${IMGUI_SOURCES}
)

set(RESOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/wall.jpg
)

file(COPY ${RESOURCE_FILES} DESTINATION ${CMAKE_BINARY_DIR})

# Specify the location of header files
target_include_directories(OpenGLApp PUBLIC include ${IMGUI_PATH})

# Add standard warning flags for better code quality
target_compile_options(OpenGLApp PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# Conditionally define the 'sandbox' preprocessor macro
if(ENABLE_SANDBOX)
    # This line adds the '-Dsandbox' flag, which is what makes #ifdef work
    target_compile_definitions(OpenGLApp PRIVATE sandbox)
endif()

# Link the required libraries to the executable
target_link_libraries(OpenGLApp
    glfw
    ${OpenGL_LIBRARIES}
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreFoundation"
)
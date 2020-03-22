cmake_minimum_required(VERSION 3.15)
project(cpp_engine)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenGL REQUIRED)

add_subdirectory(include/glfw-3.3.2)
add_subdirectory(include/glad/)
add_subdirectory(include/glm-0.9.7.1)


## main file
add_executable(cpp_engine main.cpp common/shader.h common/shader.cpp )

target_link_libraries(cpp_engine PRIVATE
        glfw
        glad
        glm
        )

target_include_directories(cpp_engine PRIVATE
        include/glad/include
     )
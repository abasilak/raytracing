# Sets the minimum required version of cmake for a project.
# If the current version of CMake is lower than that required it will stop
# processing the project.
cmake_minimum_required (VERSION 2.6)

project (RayTracing)

### enable C++11 standard
set (CMAKE_CXX_STANDARD 11) 
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")

add_definitions(-DEXECUTION_TIME_COMPUTATION)

# Create an executable binary
add_executable(RayTracing
               Vec3.cpp
               RayTracing.cpp
               Scene.cpp
               Image2D.cpp
               Camera.cpp
               Sphere.cpp
               Material.cpp
               ObjectList.cpp
               main.cpp)

message(STATUS "Building RayTracing Project")
# Sets the minimum required version of cmake for a project.
# If the current version of CMake is lower than that required it will stop
# processing the project.
cmake_minimum_required (VERSION 2.8.3)

project (RayTracing)

message(STATUS "Building RayTracing Project")

### enable C++11 standard
set (CMAKE_CXX_STANDARD 11) 
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

# OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_definitions(-DEXECUTION_TIME_COMPUTATION
                -DRANDOM_SCENE
               )

# Create an executable binary
add_executable(RayTracing
               Vec3.cpp
               Aabb.cpp
               BvhNode.cpp
               RayTracing.cpp
               Scene.cpp
               Image2D.cpp
               Camera.cpp
               Sphere.cpp
               Material.cpp
               ObjectList.cpp
               main.cpp)
cmake_minimum_required(VERSION 3.23)
project(Projet_Synthese_Images)

set(CMAKE_CXX_STANDARD 20)

add_executable(Projet_Synthese_Images main.cpp Primitives/Cube.h Primitives/Point.h Primitives/Cube.cpp Tortue.cpp Tortue.h Primitives/Sphere.cpp Primitives/Sphere.h)
target_link_libraries(Projet_Synthese_Images GLU GL glut jpeg)
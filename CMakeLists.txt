cmake_minimum_required(VERSION 3.13)
project(quarto)

set(CMAKE_CXX_STANDARD 17)

add_executable(quarto main.cpp src/Pion.cpp src/Pion.h src/Grille.cpp src/Grille.h src/Case.cpp src/Case.h src/Jeu.cpp src/Jeu.h)
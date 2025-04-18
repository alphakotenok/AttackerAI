#!/bin/bash

clang++ -o main -std=c++20 -I/opt/homebrew/include \
-L/opt/homebrew/lib \
-lsfml-graphics \
-lsfml-window \
-lsfml-system \
-lsfml-network \
main.cpp \
camera.cpp \
background.cpp \
structure_grid.cpp \
structure.cpp \
image_shape.cpp \
tower.cpp \
unit.cpp \
unit_grid.cpp \
sergei.cpp \
bullet.cpp \
bullet_manager.cpp \

./main

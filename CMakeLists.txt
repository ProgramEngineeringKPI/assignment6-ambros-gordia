cmake_minimum_required(VERSION 3.9)
project(lab6)

set(CMAKE_CXX_STANDARD 11)

add_executable(lab6 src/main.cpp src/utils/tracer/Tracer.cpp src/utils/tracer/Vector.cpp src/utils/tracer/Tracer.h src/utils/rtree/RTree.cpp src/utils/rtree/RTree.h src/utils/render/Render.cpp src/utils/render/Render.h)
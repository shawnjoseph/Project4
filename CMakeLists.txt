cmake_minimum_required(VERSION 3.5)
project(Project4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Vertex.h Edge.h Graph.h HashTable.h AdjacencyList.h Digraph.h)
add_executable(Project4 ${SOURCE_FILES})
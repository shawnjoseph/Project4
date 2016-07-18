cmake_minimum_required(VERSION 3.5)
project(Project4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CommandProcessor.cpp Menu.cpp Vertex.h Edge.h Graph.h HashTable.h AdjacencyListNode.h AdjacencyList.h Digraph.h Stack.h Queue.h minHeap.h minHeapNode.h CommandProcessor.h Menu.h)
add_executable(Project4 ${SOURCE_FILES})
cmake_minimum_required(VERSION 2.8.12)
project(pathfinding)
set(CMAKE_BUILD_TYPE Release)

include_directories(.
					./AAL)
					
set(SOURCES
	./AAL/main.cpp
	./AAL/AStar.cpp
	./AAL/BellmanFord.cpp
	./AAL/Coords.cpp
	./AAL/DataGenerator.cpp
	./AAL/Dijkstra.cpp
	./AAL/Field.cpp
	./AAL/Heap.cpp
	./AAL/Raster.cpp
	./AAL/TableLine.cpp
	./AAL/Timer.cpp
   )

set(PROJECT_LINK_LIBS
	)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(pathfinding ${SOURCES})
target_link_libraries(pathfinding ${PROJECT_LINK_LIBS})

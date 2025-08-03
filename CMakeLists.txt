cmake_minimum_required(VERSION 3.10)
project(BitsAndPieces LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

add_subdirectory(external/MiniGL)
add_subdirectory(external/MostlyForces)

# Collect sources
file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.c
)
list(REMOVE_ITEM LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# Build as a static library
add_library(BitsAndPieces STATIC ${LIB_SOURCES})
target_include_directories(BitsAndPieces PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(BitsAndPieces PUBLIC MiniGL)
target_link_libraries(BitsAndPieces PUBLIC MostlyForces)

set(APP_SOURCES src/main.cpp)

# Build as an Executable
add_executable(BitsAndPiecesApp ${APP_SOURCES})
target_link_libraries(BitsAndPiecesApp PRIVATE BitsAndPieces)

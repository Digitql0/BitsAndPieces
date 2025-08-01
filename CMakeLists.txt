cmake_minimum_required(VERSION 3.10)
project(BitsAndPieces LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

# Collect sources
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
    src/*.c
)

# Build as a static library
add_library(BitsAndPieces STATIC ${SOURCES})

# Build as an Executable
add_executable(BitsAndPiecesApp ${SOURCES})

# Include header for BitsAndPiecesApp
target_include_directories(BitsAndPiecesApp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(BitsAndPiecesApp PRIVATE BitsAndPieces)

# Include headers for anyone linking BitsAndPieces
target_include_directories(BitsAndPieces PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

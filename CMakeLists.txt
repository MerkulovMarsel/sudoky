cmake_minimum_required(VERSION 3.20)

project(merkmarsel-sudoku)


set(CMAKE_CXX_STANDARD 20)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")



set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin.dbg)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin.rel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_CURRENT_SOURCE_DIR}bin.relwithdbg)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-16>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-16>")

add_subdirectory(sudoku)
add_subdirectory(app.test)


add_executable(app app.cpp)
target_link_libraries(app sudoku)

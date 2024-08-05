add_library(sudoku sudoku.hpp sudoku.cpp)

set_property(TARGET sudoku PROPERTY CXX_STANDARD 20)

target_include_directories(sudoku PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)

install(TARGETS sudoku)
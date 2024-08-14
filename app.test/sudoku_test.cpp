#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


#include <sudoku/sudoku.hpp>


TEST_CASE("sudoku ctor") {
  Sudoku sudoku;
  CHECK_EQ(sudoku.Get_Size(), 9);
}


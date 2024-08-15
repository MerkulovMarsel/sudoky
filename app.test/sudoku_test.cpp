#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <sudoku/sudoku.hpp>


TEST_CASE("Ceil ctor") {
  Ceil ceil;
  CHECK_EQ(ceil.Get_Value(), 0);
  CHECK_EQ(ceil.Is_Visible(), true);
  Ceil ceil1(2, false);
  CHECK_EQ(ceil1.Get_Value(), 2);
  CHECK_EQ(ceil1.Is_Visible(), false);
}

TEST_CASE("Coord ceil") {
  Coord pos;
  CHECK_EQ(pos.Get_Column(), 0);
  CHECK_EQ(pos.Get_Row(), 0);
  Coord pos1(3, 6);
  CHECK_EQ(pos1.Get_Column(), 6);
  CHECK_EQ(pos1.Get_Row(), 3);
  CHECK_EQ(pos.Get_Index(), 0);
  try {
    Coord pos2(100, 1000);
  }
  catch (std::runtime_error) {}
  try {
    Coord pos2(-1000, 1);
  }
  catch (std::runtime_error) {}
}


TEST_CASE("out ctor") {
  short int  a = 6;
  int b = 6;
  CHECK_EQ(a, b);
}
TEST_CASE("sudoku ctor") {
  Sudoku sudoku;
  CHECK_EQ(sudoku.Get_Size(), 9);
}



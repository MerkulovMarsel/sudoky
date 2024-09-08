#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <sudoku/sudoku.hpp>

using namespace Sudoku;

TEST_CASE("Ceil ctor") {
  Ceil ceil;
  CHECK_EQ(ceil.Get_Value(), 0);
  CHECK_EQ(ceil.Get_Visible(), true);
  Ceil ceil1(2, false);
  CHECK_EQ(ceil1.Get_Value(), 2);
  CHECK_EQ(ceil1.Get_Visible(), false);
}

TEST_CASE("Coord ceil") {
  Coord pos;
  CHECK_EQ(pos.Get_Column(), 0);
  CHECK_EQ(pos.Get_Row(), 0);
  Coord pos1(3, 6);
  CHECK_EQ(pos1.Get_Column(), 3);
  CHECK_EQ(pos1.Get_Row(), 6);
  CHECK_EQ(pos.Get_Index(), 0);
  try {
    Coord pos2(100, 1000);
    std::cout << "NO OK";
  }
  catch (std::runtime_error) {}
  try {
    Coord pos2(-1000, 1);
    std::cout << "NO OK";
  }
  catch (std::runtime_error) {}
}


TEST_CASE("Mask ctor") {
  for (int seed = 0; seed < (1 << 15); ++seed) {
    Game g(seed, 1, 0);
  }
}

TEST_CASE("Field issue") {
  Field f;
  Coord c(0, 0);
  CHECK_EQ(f[c].Get_Value(), f.Get_Value(c));
  Ceil a(4, true);
  f[c] = a;
  CHECK_EQ(f[c].Get_Value(), f.Get_Value(c));
  int b = f[c].Get_Value();
  int d = f.Get_Value(c);
  CHECK_EQ(b,d);
}


TEST_CASE("game ctor") {
  Game game;
  CHECK_EQ(game.Get_Size(), 9);
}



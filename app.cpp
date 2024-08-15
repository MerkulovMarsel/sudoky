#include <sudoku/sudoku.hpp>
#include <iostream>




int main(int argc, char** argv ) {
  Sudoku game;
  game.Initialaze(0, 3);
  int x = 0;
  int y = 0;
  short int value = 0;
  while (!game.Is_Game_Over()) {
    game.Out();
    std::cin >> x >> y >> value;
    Coord pos(x, y);
    game.Move(pos, value);
  }
  std::cout << "GG" << std::endl;
}
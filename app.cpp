#include <sudoku/sudoku.hpp>
#include <iostream>


using namespace Sudoku;

int main(int argc, int** argv ) {
  Game game;
  game.Initialaze(1, 3);
  int x = 0;
  int y = 0;
  int value = 0;
  while (!game.Is_Game_Over()) {
    game.Out();
    std::cin >> value;
    std::cin >> x >> y;
    Coord pos(x, y);
    game.Move(pos,value);
  }
  std::cout << "GG" << std::endl;
}
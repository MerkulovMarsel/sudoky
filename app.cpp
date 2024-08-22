#include <sudoku/sudoku.hpp>
#include <iostream>


int main(int argc, int** argv ) {
  int seed = 80;
  int availiable_mistakes = 1;
  int diff = 0;
  Sudoku::Game game{seed,availiable_mistakes,diff};
  int x = 0;
  int y = 0;
  int value = 0;
  while (!game) {
    game.Out();
    std::cin >> value;
    std::cin >> x >> y;
    game.Move(x, y, value);
  }
}
#include <sudoku/sudoku.hpp>

//Seed

Sudoku::Seed::Seed(unsigned int seed) {
  for (int i = 0; i < 24; ++i) {
    seed_[i] = seed % 2;
    seed /= 2;
  }
}


//Valuevc
int Sudoku::Value::Base_Construct(const Coord& pos) const {
  return (pos.Get_Row() + pos.Get_Column() * 3) % 9 + 1;
}


int Sudoku::Value::Init(const Coord& pos) const {
  return Base_Construct(pos);
}


//Mask

Sudoku::Mask::Mask(const int diff, const Seed& seed) : diff_{ diff }, seed_{seed} {
  if (diff == 0) {
    hiden_ceils_ = 1;
  }
}

bool Sudoku::Mask::Init(const Coord& pos) const {
  if (diff_ == 0) {
    return (pos != 0);
  }
}




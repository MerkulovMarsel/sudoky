#include <sudoku/sudoku.hpp>

//Seed

Sudoku::Seed::Seed(unsigned int seed) {
  for (int i = 0; i < 24; ++i) {
    seed_[i] = (seed % 2);
    seed /= 2;
  }
  
}


//Valuevc
int Sudoku::Value::Base_Construct(const Coord& pos) const noexcept {
  return (pos.Get_Row() * size_ + pos.Get_Column() + pos.Get_Row() / size_) % (size_ * size_) + 1;
}


int Sudoku::Value::Init(const Coord& pos) const noexcept {
  return Base_Construct(pos);
}


//Mask

Sudoku::Mask::Mask(const int diff, const Seed& seed) : diff_{ diff }, seed_{seed} {
  if (diff == 0) {
    hiden_ceils_ = 1;
  }
  else {
    hiden_ceils_ = 81;
  }
}

bool Sudoku::Mask::Init(const Coord& pos) const noexcept {

  if (diff_ == 0) {
    int n = 0;
    for (int i = 0; i < 7; ++i) {
      if (seed_[i]) {
        n += (1 << i);
      }
    }
    if ((n < 81) && (n > 0) ) {
      return pos != n;
    }
    return pos != 0;
  }
  else {
    return false;
  }
}




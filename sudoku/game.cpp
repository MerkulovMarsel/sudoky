#include <sudoku/sudoku.hpp>
#include <array>



void Sudoku::Game::Initialaze(const int b_seed,const int availiable_mistakes, const int diff) {
  Seed seed(b_seed);
  Mask mask(diff,seed);
  Value value(seed);
  availiable_mistakes_ = availiable_mistakes;
  hiden_ceils_ = mask.Get_Hiden_Ceils();
  do {
    fieald_.Generate_Field(mask, value);
    fieald_.Good_Field();
  } while (!Is_Reacheable());
}

void Sudoku::Game::Initialaze(const std::string& b_seed, const int availiable_mistakes, const int diff) {
  Seed seed(b_seed);
  Mask mask(diff, seed);
  Value value(seed);
  availiable_mistakes_ = availiable_mistakes;
  hiden_ceils_ = mask.Get_Hiden_Ceils();
  do {
    fieald_.Generate_Field(mask, value);
    //fieald_.Good_Field();
  } while (!Is_Reacheable());
}

void Sudoku::Game::Out() const {
  for (int i = -1; i < 9; ++i) {
    for (int j = -1; j < 9; ++j) {
      if (i < 0 or j < 0) {
        if (i >= 0) {
          std::cout << "  " << i << "   ";
        }
        else if (j >= 0) {
          std::cout << "  " << j << "   ";
        }
        else {
          std::cout << "      ";
        }
      }
      else {
        Coord pos(j, i);
        /*Ceil c = fieald_.Get_Ceil(pos);
        c.Out_Ceil();*/
        fieald_[pos].Out_Ceil();
      }
      if (j == 2 or  j== 5) {
        std::cout << "|| ";
      }
    }
    std::cout << "\n";
    if (i == 2 or i == 5) {
      for (int k = -1; k < 9; ++k) {
        std::cout << "______";
      }
      std::cout << "\n";
      for (int k = -1; k < 9; ++k) {
        std::cout << "______";
      }
      std::cout << "\n";
      std::cout << "\n";
    }
  }
}



void Sudoku::Game::Move(const Coord& pos, const int value) {
  if (fieald_[pos].Is_Visible()) {
    std::cout << "\nValue of this ceils is availiable\n";
  }
  else {
    if (fieald_.Get_Value(pos) == value) {
      fieald_[pos].Make_Visible();
      --hiden_ceils_;
    }
    else {
      --availiable_mistakes_;
      std::cout << "\nWrong value!\n";
    }
  }
}




bool Sudoku::Game::Is_Game_Over() const noexcept {
  if (availiable_mistakes_ <= 0 || hiden_ceils_ <= 0) {
    std::cout << "\nGG" << std::endl;
    return true;
  }
  return false;
}





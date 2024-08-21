#include <sudoku/sudoku.hpp> 

void Sudoku::Ceil::Set_Ceil(const int value, const bool visible) noexcept {
  value_ = value;
  visible_ = visible;
}

void Sudoku::Ceil::Out_Ceil() const {
  if (visible_) {
    std::cout << "[ " << value_ << " ] ";
  }
  else {
    std::cout << "[ " << "?" << " ] ";
  }
}
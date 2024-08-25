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


int Sudoku::Value::Init(Coord pos) const noexcept {
  //Segment row
  for (Changer i; i.End(); i.Next()) {
    if (seed_.Seqment_Row_Switch(i.x, i.y)) {
      std::cout << " sr ";
      pos.Segment_Row_Change(i.x, i.y);
    }
  }
  //Segment column
  for (Changer i; i.End(); i.Next()) {
    if (seed_.Seqment_Column_Switch(i.x, i.y)) {
      std::cout << " sc ";
      pos.Segment_Column_Change(i.x, i.y);
    }
  }
  //Row in Segment
  for (Changer i; i.End(); i.Next()) {
    if (seed_.Row_Change_in_Segment(pos.Get_Segment(), i.x, i.y)) {
      std::cout << " r ";
      pos.Row_Change((pos.Get_Segment() / size_) + i.x, (pos.Get_Segment() / size_) + i.y);
    }
  }
  //Column in Segment
  for (Changer i; i.End(); i.Next()) {
    if (seed_.Column_Change_in_Segment(pos.Get_Segment(), i.x, i.y)) {
      std::cout << " c ";
      pos.Column_Change((pos.Get_Segment() % size_) + i.x, (pos.Get_Segment() % size_) + i.y);
    }
  }

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
    return pos != (n % 81);
  }
  else {
    return false;
  }
}




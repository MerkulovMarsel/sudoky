#include <sudoku/sudoku.hpp>
#include <array>

void Sudoku::Field::Generate_Field(const Mask& mask, const Value& value) {
  for (Coord i(0, 0); i < Coord(0, 9); ++i) {
    data_[i.Get_Index()].Set_Ceil(value(i), mask(i));
  }
}


Sudoku::Field::ProxyCeil Sudoku::Field::operator[] (const Coord& pos) {
  ProxyCeil temp(*this, pos);
  return temp;
}




Sudoku::Field::ProxyCeil Sudoku::Field::operator[] (const Coord& pos) const {
  Field tmp = *this;
  ProxyCeil temp(tmp, pos);
  return temp;
}




Sudoku::Field::ProxyCeil& Sudoku::Field::ProxyCeil::operator=(const Ceil& ceil) {
  field_.data_[pos_.Get_Index()] = ceil;
  ceil_ = ceil;
  return *this;
}


void Sudoku::Field::Good_Field() const {
  bool bad_field = false;
  for (Coord pos; pos < size_ * size_; ++pos) {
    for (Coord i{ 0,pos.Get_Row() }; i < Coord(8, pos.Get_Row()); ++i) {
      if ((i != pos) && (data_[pos.Get_Index()] == data_[i.Get_Index()].Get_Value())) {
        bad_field = true;
        break;
      }
    }
    for (Coord i{pos.Get_Column(), 0 }; i < Coord( pos.Get_Column(), 8); i += 9) {
      if ((i != pos) && (data_[pos.Get_Index()] == data_[i.Get_Index()].Get_Value())) {
        bad_field = true;
        break;
      }
    }
    for (int j = 0; j < 3; ++j) {
      for (Coord i{ (pos.Get_Segment() % 3) * 3 , j + (pos.Get_Segment() / 3) * 3 }; i < Coord((pos.Get_Segment() % 3) * 3 + 3, j + (pos.Get_Segment() / 3) * 3); ++i) {
        if ((i != pos) && (data_[pos.Get_Index()] == data_[i.Get_Index()].Get_Value())) {
          bad_field = true;
          break;
        }
      }
    }
  }
  if (bad_field) {
    throw std::runtime_error("bad field");
  }
}
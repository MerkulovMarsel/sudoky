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




bool Sudoku::Field::Is_Visible(const Coord pos) {
  return data_[pos.Get_Index()].Get_Visible();
}

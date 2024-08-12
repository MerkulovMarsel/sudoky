#include "sudoku.hpp"

void Mask::Simply_Init() {
  for (auto it = mask.begin(); it != mask.end(); ++it) {
    *it = true;
  }
}

bool Mask::operator[](const Coord& pos) {
  return mask[pos.Get_Index()];
}

void Value::Simply_Init() {
  int v = 0;
  for (auto it = value.begin(); it != value.end(); ++it) {
    *it = (v++ + v/9)%9 + 1;
  }
}

std::int8_t Value::operator[](const Coord& pos) {
  return value[pos.Get_Index()];
}

void Sudoku::Initialaze(const int key = 0, std::int8_t available_mistakes = 3) {
  Mask mask(key);
  Value value(key);
  fieald_.Generate_Field(mask,value);
  availiable_mistakes_ = available_mistakes;
}


std::array<Ceil,81> Sudoku::Out() const {

}

void Sudoku::Move(const Coord& pos, const int value) {

}


bool Sudoku::Is_Game_Over() {
  return (availiable_mistakes_ == 0);
}



void Field::Generate_Field(const Mask& mask, const Value& value) {
  for (Coord i(0,0); i < Coord(0,9); ++i) {
    data_[i.Get_Index()] = (value[i], mask[i]);
  }
}

Field::ProxyCeil& Field::operator[] (const Coord& pos) {

}


Field::ProxyCeil& Field::operator[] (const Coord& pos) {

}


bool Field::Is_Visible(const Coord& pos) {
  return data_[pos.Get_Index()].Is_Visible();
}



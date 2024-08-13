#include "sudoku.hpp"

void Mask::Simply_Init() {
  for (auto it = mask.begin(); it != mask.end(); ++it) {
    *it = true;
  }
}

bool Mask::operator[](const Coord& pos) const {
  return mask[pos.Get_Index()];
}

void Value::Simply_Init() {
  int v = 0;
  for (auto it = value.begin(); it != value.end(); ++it) {
    *it = (v++ + v/9)%9 + 1;
  }
}

std::int8_t Value::operator[](const Coord& pos) const {
  return value[pos.Get_Index()];
}

void Sudoku::Initialaze(const int key = 0, std::int8_t available_mistakes = 3) {
  Mask mask(key);
  Value value(key);
  fieald_.Generate_Field(mask,value);
  availiable_mistakes_ = available_mistakes;
}


void Sudoku::Out() const {
  for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
      std::cout << "[ " << fieald_[Coord(j, i)].Get_Value() << " ]  ";
    }
    std::cout << "\n";
  }
}

void Sudoku::Move(const Coord& pos, const std::int8_t value) {
  if (fieald_[pos].Is_Visible()) {
    std::cout << "\nValue of this ceils is availiable\n";
  }
  else {
    if (fieald_[pos].Get_Value() == value) {

    }
    else {
      --availiable_mistakes_;
      std::cout << "\nWrong value!\n";
    }
  }
}


bool Sudoku::Is_Game_Over() {
  return (availiable_mistakes_ == 0);
}



void Field::Generate_Field(const Mask& mask, const Value& value) {
  for (Coord i(0,0); i < Coord(0,9); ++i) {
    data_[i.Get_Index()].Set_Ceil(value[i], mask[i]);
  }
}

Field::ProxyCeil& Field::operator[] (const Coord& pos) {
  ProxyCeil temp(*this, pos);
  return temp;
}

Field::ProxyCeil& Field::operator[] (const Coord& pos) const {
  Field tmp = *this;
  ProxyCeil temp(tmp, pos);
  return temp;
}

Field::ProxyCeil& Field::ProxyCeil::operator=(const Ceil& ceil) {
  field_.data_[pos_.Get_Index()] = ceil;
  ceil_ = ceil;
  return *this;
}

bool Field::Is_Visible(const Coord& pos) {
  return data_[pos.Get_Index()].Is_Visible();
}



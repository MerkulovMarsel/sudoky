#include <sudoku/sudoku.hpp>
#include <array>

void Mask::Simply_Init() {
  int m = 78;
  for (auto it = mask.begin(); it != mask.end(); ++it) {
    if (m == 0) {
      *it = false;
    }else{*it = true;}
    --m;
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



short int Value::operator[](const Coord& pos) const {
  return value[pos.Get_Index()];
}



void Sudoku::Initialaze(const int key, short int availiable_mistakes) {
  Mask mask(key);
  Value value(key);
  fieald_.Generate_Field(mask,value);
  availiable_mistakes_ = availiable_mistakes;
}



void Sudoku::Out() const {
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
        fieald_[pos].Out_Ceil();
      }
    }
    std::cout << "\n";
  }
}



void Sudoku::Move(const Coord& pos, const short int value) {
  if (fieald_[pos].Is_Visible()) {
    std::cout << "\nValue of this ceils is availiable\n";
  }
  else {
    if (fieald_[pos].Get_Value() == value) {
      fieald_[pos].Make_Visible();
    }
    else {
      --availiable_mistakes_;
      std::cout << "\nWrong value!" << value << fieald_[pos].Get_Value() <<"\n";;
    }
  }
}




bool Sudoku::Is_Game_Over() const {
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




bool Field::Is_Visible(const Coord pos) {
  return data_[pos.Get_Index()].Is_Visible();
}


void Ceil::Set_Ceil(const short int value, const bool visible) {
  value_ = value;
  visible_ = visible;
}

void Ceil::Out_Ceil() const {
  if (visible_) {
    std::cout << "[ " << static_cast<int>(value_) << " ] ";
  }
  else {
    std::cout << "[ " << "?" << " ] ";
  }
}
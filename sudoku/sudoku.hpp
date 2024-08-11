#include <vector>
#include <iostream>



class Sudoku {
public:
  void Initialaze(const int size, std::int8_t availiable_mistakes);

  std::vector<Ceil> Out() const; 

  void Move(const Coord& pos, const int value);

  bool Is_Game_Over();

  static inline int Get_Size() { return size_; };
private:
  Field fieald_;
  std::int8_t availiable_mistakes_ = 0;
  static const int size_ = 9;
};



class Field {
public:
  void Generate_Field();

  Ceil Take_ceil(const int x, const int y) const;


  void Set_Ceil(const int x, const int y, std::int8_t value);


  bool Is_Visible(const Coord& pos);
private:
  std::vector<Ceil> data_;
  int size_ = 0;
};


class Coord {
public:
  inline Coord(const int x, const int y) :x_(x), y_(y), size_(Sudoku::Get_Size()) {};

private:
  int x_ = 0;
  int y_ = 0;
  int size_ = 9;
};


class Ceil
{
public:

  void Set_Ceil(const std::int8_t value, const bool visible);

private:
  std::int8_t value_ = 0;
  bool visible_ = true;
};
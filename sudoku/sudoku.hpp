#include <iostream>
#include <array>

class Mask {
public:
  inline Mask(const int key) {
    Simply_Init();
  }
  void Simply_Init();
  bool operator[](const Coord& pos);
private:
  std::array<bool, 81> mask;
};

class Value {
public:
  inline Value(const int key) {
    Simply_Init();
  }
  void Simply_Init();
  std::int8_t operator[](const Coord& pos);
private:
  std::array<std::int8_t, 81> value;
};

class Sudoku {
public:
  void Initialaze(const int key = 0, std::int8_t availiable_mistakes = 3);

  std::array<Ceil, 81> Out() const;

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
  class ProxyCeil {
  public:

    ProxyCeil& operator=(const Ceil& ceil);
  private:
    Field& field_;
    Ceil ceil;
  };
  void Generate_Field(const Mask& mask, const Value& value);


  bool Is_Visible(const Coord& pos);


  ProxyCeil& operator[] (const Coord& pos);
private:
  std::array<Ceil,81> data_;
  static const int size_ = 9;
};


class Coord {
public:
  inline void operator++() { ++index_; };

  inline Coord(const int x, const int y) :index_(x + y * 9), size_(Sudoku::Get_Size()) {};

  inline int Get_Index() const { return index_; };

  inline bool operator<(const Coord& pos) { return index_ < pos.Get_Index(); };
private:
  int index_ = 0;
  int size_ = 9;
};


class Ceil
{
public:
  Ceil(std::int8_t value, bool vis): value_(value), visible_(vis){};

  void Set_Ceil(const std::int8_t value, const bool visible);

  inline bool Is_Visible() const { return visible_; }
private:
  std::int8_t value_ = 0;
  bool visible_ = true;
};
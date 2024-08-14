#pragma once
#include <iostream>
#include <array>

class Mask {
public:
  inline Mask(const int key) {
    Simply_Init();
  }
  void Simply_Init();
  bool operator[](const Coord& pos) const; //
private:
  std::array<bool, 81> mask;
};





class Value {
public:
  inline Value(const int key) {
    Simply_Init();
  }
  void Simply_Init();
  std::int8_t operator[](const Coord& pos) const; //
private:
  std::array<std::int8_t, 81> value;
};






class Sudoku {
public:
  void Initialaze(const int key = 0, std::int8_t availiable_mistakes = 3);

  void Out() const;

  void Move(const Coord& pos, const std::int8_t value); //

  bool Is_Game_Over();

  static inline int Get_Size() { return size_; };

private:
  Field fieald_;//
  std::int8_t availiable_mistakes_ = 0;
  static const int size_ = 9;
};





class Field {
public:
  class ProxyCeil {
  public:
    ProxyCeil(Field& field, const Coord& pos) ://
      field_(field), pos_(pos_), ceil_(field_.data_[pos_.Get_Index()]) {};

    ProxyCeil& operator=(const Ceil& ceil);//

    inline bool Is_Visible() const { return field_.data_[pos_.Get_Index()].Is_Visible(); }

    inline std::int8_t Get_Value() const { ceil_.Get_Value(); };

    inline void Make_Visible() { field_.data_[pos_.Get_Index()].Make_Visible(); }


  private:
    Field& field_;
    Coord pos_;//
    Ceil ceil_;//
  };
  void Generate_Field(const Mask& mask, const Value& value);


  bool Is_Visible(const Coord pos);//


  ProxyCeil& operator[] (const Coord& pos);

  ProxyCeil& operator[] (const Coord& pos) const;

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

  inline void Make_Visible() { visible_ = true; };

  inline bool Is_Visible() const { return visible_; }

  inline std::int8_t Get_Value() const { return value_; };
private:
  std::int8_t value_ = 0;
  bool visible_ = true;
};


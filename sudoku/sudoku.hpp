#pragma once
#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <iostream>
#include <array>


class Ceil
{
public:
  inline Ceil() { value_ = 0; visible_ = true; };

  Ceil(short int value, bool vis): value_(value), visible_(vis){};

  void Set_Ceil(const short int value, const bool visible);

  inline void Make_Visible() { visible_ = true; };

  inline bool Is_Visible() const { return visible_; }

  inline short int Get_Value() const { return value_; };

  void Out_Ceil() const ;
private:
  short int value_ = 0;
  bool visible_ = true;
};

class Coord {
public:

  inline void operator++() { ++index_; };

  inline Coord() = default;

  inline Coord(const int x, const int y) :index_(x + y * size_) {};

  inline int Get_Row() const { return index_ % size_; };

  inline int Get_Column() const { return index_ / size_; };

  inline int Get_Index() const { return index_; };

  inline bool operator<(const Coord& pos) { return index_ < pos.Get_Index(); };
private:
  int index_ = 0;
  static const int size_ = 9;
};



class Mask {
public:
  inline Mask(const int key) {
    Simply_Init();
  }
  void Simply_Init();
  bool operator[](const Coord& pos) const; 
private:
  std::array<bool, 81> mask;
};



class Value {
public:
  inline Value(const int key) {
    Simply_Init();
  }
  void Simply_Init();
  short int operator[](const Coord& pos) const; 
private:
  std::array<short int, 81> value;
};



class Field {
public:
  class ProxyCeil {
  public:
    ProxyCeil(Field& field, const Coord& pos) :
      field_(field), pos_(pos), ceil_(field_.data_[pos_.Get_Index()]) {};

    ProxyCeil& operator=(const Ceil& ceil);

    inline bool Is_Visible() const { return field_.data_[pos_.Get_Index()].Is_Visible(); };

    inline short int Get_Value() const { return ceil_.Get_Value(); };

    inline void Make_Visible() { field_.data_[pos_.Get_Index()].Make_Visible(); };

    inline void Out_Ceil() { ceil_.Out_Ceil(); };
  private:
    Field& field_;
    Coord pos_;
    Ceil ceil_;
  };

  void Generate_Field(const Mask& mask, const Value& value);


  bool Is_Visible(const Coord pos);


  ProxyCeil& operator[] (const Coord& pos);

  ProxyCeil& operator[] (const Coord& pos) const;

private:
  std::array<Ceil,81> data_;
  static const int size_ = 9;
};


class Sudoku {
public:

  void Initialaze(const int key = 0, short int availiable_mistakes = 3);

  void Out() const;

  void Move(const Coord& pos, const short int value);

  bool Is_Game_Over() const;

  static inline int Get_Size() { return size_; };

private:
  Field fieald_;
  short int availiable_mistakes_ = 0;
  static const int size_ = 9;
};





#endif // !SUDOKU_HPP

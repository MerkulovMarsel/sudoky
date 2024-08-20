#pragma once
#ifndef Sudoku_HPP
#define Sudoku_HPP

#include <iostream>
#include <array>
#include <bitset>




namespace Sudoku {
  class Ceil
  {
  public:

    inline Ceil() { value_ = 0; visible_ = true; };

    Ceil(int value, bool vis) : value_(value), visible_(vis) {};

    void Set_Ceil(const int value, const bool visible);

    inline void Make_Visible() { visible_ = true; };

    inline bool Is_Visible() const { return visible_; }

    inline int Get_Value() const { return value_; };

    void Out_Ceil() const;

    //Ceil& operator=(const Field::ProxyCeil& ceil) { value_ = ceil.Get_Value(); visible_ = ceil.Is_Visible(); }

    bool operator==(const Ceil& ceil) { return (value_ == ceil.Get_Value()) && (visible_ == ceil.Is_Visible()); }
  private:
    int value_ = 1;
    bool visible_ = true;
  };

  class Coord {
  public:

    inline void operator++() { ++index_; };

    inline Coord() = default;

    inline Coord(const int x, const int y) {
      if (x < 0 || x > size_ || y < 0 || y> size_) {
        throw std::runtime_error("Invalid argument");
      }
      else {
        index_ = x + size_ * y;
      }
    }

    inline int Get_Row() const { return index_ % size_; };

    inline int Get_Column() const { return index_ / size_; };

    inline int Get_Index() const { return index_; };

    inline bool operator<(const Coord& pos) { return index_ < pos.Get_Index(); };

    inline bool operator==(const Coord& pos) const { return index_ == pos.Get_Index(); }

    inline bool operator==(const int pos) const { return index_ == pos; }

  private:
    int index_ = 0;
    static const int size_ = 9;
  };

  class Seed {
  public:
    Seed(unsigned int seed = 0);
    inline bool operator[](const int pos) { return seed_[pos]; }
  private:
    std::bitset<24> seed_;
  };




 class Value {
  public:

    inline Value(const Seed& seed = 0): seed_(seed){}

    int Init(const Coord& pos) const;

    inline int operator()(const Coord& pos) const { return Init(pos); }

    int Base_Construct(const Coord& pos) const;
  private:
    Seed seed_;
  };

class Mask {
  public:
    inline Mask() : diff_{ 0 }, hiden_ceils_{ 1 }, seed_{ 0 } {}

    Mask(const int diff, const Seed& seed);

    bool Init(const Coord& pos) const;

    inline bool operator()(const Coord& pos) const { return Init(pos); }

  private:
    int diff_ = 0;
    int hiden_ceils_ = 0;
    Seed seed_;
  };

  class Field {
  public:
    class ProxyCeil {
    public:
      ProxyCeil(Field& field, const Coord& pos) :
        field_(field), pos_(pos), ceil_(field_.data_[pos_.Get_Index()]) {}

      ProxyCeil& operator=(const Ceil& ceil);

      inline bool Is_Visible() const { return ceil_.Is_Visible(); }

      inline int Get_Value() const { return ceil_.Get_Value(); }

      inline void Make_Visible() { field_.data_[pos_.Get_Index()].Make_Visible(); }

      inline void Out_Ceil() { ceil_.Out_Ceil(); }

      inline bool operator==(const int val) {
        return ceil_.Get_Value() == val;
      }

      inline bool operator==(const Ceil& ceil) {
        return ceil == ceil_;
      }

    private:
      Field& field_;
      Coord pos_;
      Ceil ceil_{ 1,false };
    };

    inline Field() { Mask m; Value v; Generate_Field(m, v); }

    inline Field(const Mask& mask, const Value& value) { Generate_Field(mask, value); }

    inline Field(const Field& field) : data_(field.data_) {}

    void Generate_Field(const Mask& mask, const Value& value);

    bool Is_Visible(const Coord pos); 

    ProxyCeil operator[] (const Coord& pos);

    ProxyCeil operator[] (const Coord& pos) const;

    inline int Get_Value(const Coord& pos) const { return data_[pos.Get_Index()].Get_Value(); }

    inline Ceil Get_Ceil(const Coord& pos) const { return data_[pos.Get_Index()]; }
  private:
    std::array<Ceil, 81> data_;
    static const int size_ = 9;
  };


  class Game {
  public:
    inline Game() = default;

    void Initialaze(const int seed = 0, int availiable_mistakes = 3);

    void Out() const;

    void Move(const Coord& pos, const int value);

    bool Is_Game_Over() const;

    static inline int Get_Size() { return size_; };

    Field Get_Field() { return fieald_; }

    bool Is_Reacheable() const { return true; }

  private:
    Field fieald_;
    int availiable_mistakes_ = 3;
    int hiden_ceils_ = 1;
    static const int size_ = 9;
  };
}




#endif // !Sudoku_HPP

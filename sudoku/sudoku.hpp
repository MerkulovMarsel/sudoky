#pragma once
#ifndef Sudoku_HPP
#define Sudoku_HPP

#include <iostream>
#include <array>
#include <bitset>


/// \brief namespace of game library that contains all classes for sudoku
namespace Sudoku {
  /// \brief class of basic ceil in game
  class Ceil
  {
  public:
    /// \brief default ctor of int value and visible of ceil
    Ceil(int value = 0, bool visible = true) : value_{ value }, visible_{ visible } {};

    /// \brief set content of ceil
    /// \param value: value in ceil
    /// \param visible: visible of ceil in game
    void Set_Ceil(const int value = 0, const bool visible = true) noexcept;

    /// \brief Make ceil visible
    inline void Make_Visible() noexcept { visible_ = true; }

    /// \return return visible of ceil
    [[nodiscard]] inline bool Get_Visible() const noexcept { return visible_; }

    /// \return return value of ceil
    [[nodiscard]] inline int Get_Value() const noexcept { return value_; };

    /// \brief print ceil 
    void Out_Ceil() const;

    /// \brief operator== for class ceil
    [[nodiscard]] bool operator==(const Ceil& ceil) const noexcept { return (value_ == ceil.Get_Value()) && (visible_ == ceil.Get_Visible()); }

    /// \brief operator== for class int value
    [[nodiscard]] bool operator==(const int value) const noexcept { return value_ == value; }
  private:
    int value_ = 0;
    bool visible_ = true;
  };

  class Coord {
  public:
    inline Coord() = default;

    inline Coord(const int x, const int y) {
      if (x < 0 || x > size_ * size_ || y < 0 || y > size_ * size_) {
        throw std::runtime_error("Invalid argument");
      }
      else {
        index_ = x + size_ * size_ * y;
      }
    }

    inline void operator++() noexcept { ++index_; };

    inline void operator+=(const int n) noexcept { index_+=n; };

    [[nodiscard]] inline bool operator<(const Coord& pos) const noexcept { return index_ < pos.Get_Index(); };

    [[nodiscard]] inline bool operator>(const Coord& pos) const noexcept { return index_ > pos.Get_Index(); };

    [[nodiscard]] inline bool operator<=(const Coord& pos) const noexcept { return index_ <= pos.Get_Index(); };

    [[nodiscard]] inline bool operator>=(const Coord& pos) const noexcept { return index_ >= pos.Get_Index(); };

    [[nodiscard]] inline bool operator<(const int pos) const noexcept { return index_ < pos; };

    [[nodiscard]] inline bool operator>(const int pos) const noexcept { return index_ > pos; };

    [[nodiscard]] inline bool operator<=(const int pos) const noexcept { return index_ <= pos; };

    [[nodiscard]] inline bool operator>=(const int pos) const noexcept { return index_ >= pos; };

    [[nodiscard]] inline bool operator==(const Coord& pos) const noexcept { return index_ == pos.Get_Index(); }

    [[nodiscard]] inline bool operator==(const int pos) const noexcept { return index_ == pos; }

    [[nodiscard]] inline bool operator!=(const int pos) const noexcept { return index_ != pos; }

    [[nodiscard]] inline int Get_Row() const noexcept { return index_ / (size_ * size_); };

    [[nodiscard]] inline int Get_Column() const noexcept { return index_ % (size_ * size_); };

    [[nodiscard]] inline int Get_Index() const noexcept { return index_; };

    [[nodiscard]] inline int Get_Segment() const noexcept { return (Get_Row() / size_) * size_ + Get_Column() / size_; };

    [[nodiscard]] inline int Get_Segment_Row() const noexcept { return Get_Segment() / size_; }

    [[nodiscard]] inline int Get_Segment_Column() const noexcept { return  Get_Segment() % size_; }

    inline void Change_To(const int x, const int y) {
      Coord tmp(x, y);
      index_ = tmp.Get_Index();
    }

    inline void Change_To(const Coord& pos) {
      index_ = pos.Get_Index();
    }

    inline void Row_Change(const int row1, const int row2) { 
      if (row1 >= row2) {
        throw std::invalid_argument("wrong row change: first argument must be less than second");
      }
      else {
        if (Get_Row() == row1) {
          Change_To(Get_Column(), row2);
        }
        else if (Get_Row() == row2) {
          Change_To(Get_Column(), row1);
        }
      }
    }

    inline void Column_Change(const int col1, const int col2) {
      if (col1 >= col2) {
        throw std::invalid_argument("wrong column change: first argument must be less than second");
      }
      else {
        if (Get_Column() == col1) {
          Change_To(col2, Get_Row());
        }
        else if (Get_Column() == col2) {
          Change_To(col1, Get_Row());
        }
      }
    }

    inline void Segment_Row_Change(const int row1, const int row2) {
      for (int i = 0; i < size_; ++i) {
        Row_Change(row1 * size_ + i, row2 * size_ + i);
      }
    }

    inline void Segment_Column_Change(const int col1, const int col2) {
      for (int i = 0; i < size_; ++i) {
        Column_Change(col1 * size_ + i, col2 * size_ + i);
      }
    }

  private:
    int index_ = 0;
    static const int size_ = 3;
  };

  class Seed {
  public:

    Seed(unsigned int seed = 0);

    inline Seed(const Seed& seed) : seed_{ seed.seed_ } {};

    [[nodiscard]] inline bool operator[](const int pos) const { return seed_[pos]; }

    inline Seed& operator=(unsigned int seed) { Seed i(seed); *this = i; return *this; }

    inline bool Seqment_Row_Switch(const int row1, const int row2) const { return seed_[row1 + row2 - 1]; }

    inline bool Seqment_Column_Switch(const int row1, const int row2) const { return seed_[row1 + row2 + size_ - 1]; }

    inline bool Row_Change_in_Segment(const int segment, const int row1, const int row2) const { return seed_[size_ * 2 + (segment / size_) * size_ + (row1 % size_) + (row2 % size_) - 1]; }

    inline bool Column_Change_in_Segment(const int segment, const int col1, const int col2) const { return seed_[size_ * 5 + (segment % size_) * size_  + (col1 % size_) + (col2 % size_) - 1]; }

  private:
    std::bitset<24> seed_;
    static const int size_ = 3;
  };




 class Value {
  public:

    inline Value(const Seed& seed = 0): seed_(seed){}

    [[nodiscard]] int Init(Coord pos) const noexcept;

    [[nodiscard]] inline int operator()(const Coord& pos) const noexcept { return Init(pos); }

    [[nodiscard]] int Base_Construct(const Coord& pos) const noexcept;

  private:
    struct Changer {
      Changer() = default;
      bool End() { return !((x >= (size_ - 2)) && (y >= (size_ - 1))); }
      void Next() {
        if (y - x == 1) {
          ++y;
        }else{
          ++x;
        }
      }
      int x = 0;
      int y = 1;
    };
    Seed seed_;
    static const int size_ = 3;
  };

class Mask {
  public:

    Mask(const int diff = 0, const Seed& seed = 0);

    [[nodiscard]] bool Init(const Coord& pos) const noexcept;

    [[nodiscard]] inline bool operator()(const Coord& pos) const noexcept { return Init(pos); }

    [[nodiscard]] inline int Get_Hiden_Ceils() const noexcept { return hiden_ceils_; }

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

      [[nodiscard]] inline bool Is_Visible() const noexcept { return ceil_.Get_Visible(); }

      [[nodiscard]] inline int Get_Value() const noexcept { return ceil_.Get_Value(); }

      inline void Make_Visible() { field_.data_[pos_.Get_Index()].Make_Visible(); }

      inline void Out_Ceil() { ceil_.Out_Ceil(); }

      [[nodiscard]] inline bool operator==(const int val) {
        return ceil_.Get_Value() == val;
      }

      [[nodiscard]] inline bool operator==(const Ceil& ceil) {
        return ceil == ceil_;
      }

    private:
      Field& field_;
      Coord pos_;
      Ceil ceil_{ 1,false };
    };

    inline Field() = default;

    inline Field(const Mask& mask, const Value& value) { Generate_Field(mask, value); }

    inline Field(const Field& field) : data_(field.data_) {}

    void Generate_Field(const Mask& mask, const Value& value);

    [[nodiscard]] inline bool Get_Visible(const Coord& pos) const { return data_[pos.Get_Index()].Get_Visible(); }

    ProxyCeil operator[] (const Coord& pos);

    ProxyCeil operator[] (const Coord& pos) const;

    [[nodiscard]] inline int Get_Value(const Coord& pos) const { return data_[pos.Get_Index()].Get_Value(); }

    [[nodiscard]] inline Ceil Get_Ceil(const Coord& pos) const { return data_[pos.Get_Index()]; }

    void Good_Field() const;
  private:
    std::array<Ceil, 81> data_;
    static const int size_ = 9;
  };


  class Game {
  public:
    inline Game(const int seed = 0, int availiable_mistakes = 0, const int diff = 0) { Initialaze(seed, availiable_mistakes, diff); }

    void Initialaze(const int seed = 0, int availiable_mistakes = 0, const int diff = 0);

    void Out() const;

    void Move(const Coord& pos, const int value);

    void Move(const int x, const int y, const int value) { Move(Coord(x, y), value); }

    bool Is_Game_Over() const noexcept;

    static inline int Get_Size() { return size_; };

    Field Get_Field() { return fieald_; }

    bool Is_Reacheable() const { return true; }

    [[nodiscard]] inline operator bool() const noexcept  { return Is_Game_Over(); }

  private:
    Field fieald_;
    int availiable_mistakes_ = 0;
    int hiden_ceils_ = 0;
    static const int size_ = 9;
  };
}




#endif // !Sudoku_HPP

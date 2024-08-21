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
      if (x < 0 || x > size_ || y < 0 || y> size_) {
        throw std::runtime_error("Invalid argument");
      }
      else {
        index_ = x + size_ * y;
      }
    }

    inline void operator++() noexcept { ++index_; };

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

    [[nodiscard]] inline int Get_Row() const noexcept { return index_ % size_; };

    [[nodiscard]] inline int Get_Column() const noexcept { return index_ / size_; };

    [[nodiscard]] inline int Get_Index() const noexcept { return index_; };
  private:
    int index_ = 0;
    static const int size_ = 9;
  };

  class Seed {
  public:

    Seed(unsigned int seed = 0);

    [[nodiscard]] inline bool operator[](const int pos) const { return seed_[pos]; }

    inline Seed& operator=(unsigned int seed) { Seed i(seed); *this = i; return *this; }

  private:
    std::bitset<24> seed_;
  };




 class Value {
  public:

    inline Value(const Seed& seed = 0): seed_(seed){}

    [[nodiscard]] int Init(const Coord& pos) const noexcept;

    [[nodiscard]] inline int operator()(const Coord& pos) const noexcept { return Init(pos); }

    [[nodiscard]] int Base_Construct(const Coord& pos) const noexcept;

  private:
    Seed seed_;
    static const int size_ = 3;
  };

class Mask {
  public:

    Mask(const int diff = 0, const Seed& seed = 0);

    [[nodiscard]] bool Init(const Coord& pos) const noexcept;

    [[nodiscard]] inline bool operator()(const Coord& pos) const noexcept { return Init(pos); }

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

      inline bool Is_Visible() const { return ceil_.Get_Visible(); }

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

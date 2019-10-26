#pragma once

#include "Base.h"
#include <tuple>
#include <vector>
namespace mat_vec {

class Matrix {
 public:
  // Конструирует матрицу с размерами size x size, заполненную value
  explicit Matrix(size_t size, double value = 0);

  // Возвращает единичную матрицу
  static Matrix eye(size_t size);

  // Возвращает матрицу с размерами rows x cols, заполненную value
  Matrix(size_t rows, size_t cols, double value = 0);

  // Конструктор копирования
  Matrix(const Matrix &src);

  // Оператор присваивания
  Matrix &operator=(const Matrix &rhs);

  // Деструктор
  ~Matrix();

  // Изменяет ширину и высоту матрицы, не изменяя при этом
  // порядок следования элементов от левого верхнего к правому нижнему:
  //
  // [1 2 3] -> [1 2]
  // [4 5 6] -> [3 4]
  //            [5 6]
  void reshape(size_t rows, size_t cols);

  // Возвращает пару {rows, cols} -- количество строк и столбцов матрицы
  std::pair<size_t, size_t> shape() const;

  // Возвращает элемент на позиции [row, col]
  double get(size_t row, size_t col) const;

  // Поэлементное сложение
  Matrix operator+(const Matrix &rhs) const;
  Matrix &operator+=(const Matrix &rhs);

  // Поэлементное вычитание
  Matrix operator-(const Matrix &rhs) const;
  Matrix &operator-=(const Matrix &rhs);

  // Матричное умножение
  Matrix operator*(const Matrix &rhs) const;
  Matrix &operator*=(const Matrix &rhs);

  // Умножение всех элементов матрицы на константу
  Matrix operator*(double k) const;
  Matrix &operator*=(double k);

  // Деление всех элементов матрицы на константу
  Matrix operator/(double k) const;
  Matrix &operator/=(double k);

  // Возвращает новую матрицу, полученную транспонированием текущей (this)
  Matrix transposed() const;

  // Транспонирует текущую матрицу
  void transpose();

  // Определитель
  double det() const;

  // Обратная матрица
  Matrix inv() const;

  // УМножение матрицы на вектор
  Vector operator*(const Vector &vec) const;

  // Поэлементное сравнение
  bool operator==(const Matrix &rhs) const;
  bool operator!=(const Matrix &rhs) const;

 private:
  std::vector<std::vector<double>> data_m;
  double rows,clo;
};

} // namespace mat_vec

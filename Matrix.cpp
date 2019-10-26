#include "Matrix.h"
#include "Vector.h"
#include <cstdlib>
#include <vector>

namespace mat_vec {
// Конструирует матрицу с размерами size x size, заполненную value
Matrix::Matrix(size_t size, double value) {
  this->clo = this->rows = value;
  for (int i = 0; i < size; i++) {
    std::vector<double> temp;
    for (int j = 1; j < size; j++) {
      temp.push_back(value);
    }
    data_m.push_back(temp);
  }
}

// Возвращает единичную матрицу
Matrix Matrix::eye(size_t size) {
  Matrix temp(size, 0.0);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (i == j) temp.data_m[i][j] = 1;
    }
  }
  return temp;
}

// Возвращает матрицу с размерами rows x cols, заполненную value
Matrix::Matrix(size_t rows, size_t cols, double value) {
  this->clo = cols;
  this->rows = rows;
  for (int i = 0; i < rows; i++) {
    std::vector<double> temp;
    for (int j = 1; j < cols; j++) {
      temp.push_back(value);
    }
    data_m.push_back(temp);
  }
}

// Конструктор копирования
Matrix::Matrix(const Matrix &src) {
  this->clo = src.clo;
  this->rows = src.rows;
  for (int i = 0; i < src.rows; i++) {
    for (int j = 0; j < src.clo; j++) {
      this->data_m[i][j] = src.data_m[i][j];
    }
  }
}
// Оператор присваивания
Matrix &Matrix::operator=(const Matrix &rhs) {
  data_m.clear();
  for (int i = 0; i < rows; i++) {
    std::vector<double> temp;
    for (int j = 1; j < clo; j++) {
      temp.push_back(rhs.data_m[i][j]);
    }
    data_m.push_back(temp);
  }
  return *this;
}

// Деструктор
Matrix::~Matrix() {
  data_m.clear();
  this->rows = 0;
  this->clo = 0;
}

// Изменяет ширину и высоту матрицы, не изменяя при этом
// порядок следования элементов от левого верхнего к правому нижнему:
//
// [1 2 3] -> [1 2]
// [4 5 6] -> [3 4]
//            [5 6]
void Matrix::reshape(size_t rows, size_t cols) {
  this->clo = rows;
  this->rows = cols;
}

// Возвращает пару {rows, cols} -- количество строк и столбцов матрицы
std::pair<size_t, size_t> Matrix::shape() const {
  return std::make_pair(this->rows, this->clo);
}
// Возвращает элемент на позиции [row, col]
double Matrix::get(size_t row, size_t col) const {
  return this->data_m[row][col];
}

// Поэлементное сложение
Matrix Matrix::operator+(const Matrix &rhs) const {
  Matrix temp(*this);
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->clo; j++) {
      temp.data_m[i][j] += rhs.data_m[i][j];
    }
  }
  return temp;
}
Matrix &Matrix::operator+=(const Matrix &rhs) {
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->clo; j++) {
      this->data_m[i][j] += rhs.data_m[i][j];
    }
  }
  return *this;
}

// Поэлементное вычитание
Matrix Matrix::operator-(const Matrix &rhs) const {
  Matrix temp(*this);
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->clo; j++) {
      temp.data_m[i][j] -= rhs.data_m[i][j];
    }
  }
  return temp;
}
Matrix &Matrix::operator-=(const Matrix &rhs) {
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->clo; j++) {
      this->data_m[i][j] -= rhs.data_m[i][j];
    }
  }
  return *this;
}

// Матричное умножение
Matrix Matrix::operator*(const Matrix &rhs) const {
  Matrix temp(*this);
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->clo; j++) {
      temp.data_m[i][j] *= rhs.data_m[i][j];
    }
  }
  return temp;
}
Matrix &Matrix::operator*=(const Matrix &rhs) {
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->clo; j++) {
      this->data_m[i][j] *= rhs.data_m[i][j];
    }
  }
  return *this;
}

// Умножение всех элементов матрицы на константу
Matrix Matrix::operator*(double k) const {
  Matrix temp(*this);
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->clo; j++) {
      temp.data_m[i][j] *= k;
    }
  }
  return temp;
}
Matrix &Matrix::operator*=(double k) {
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->clo; j++) {
      this->data_m[i][j] *= k;
    }
  }
  return *this;
}

// Деление всех элементов матрицы на константу
Matrix Matrix::operator/(double k) const {
  Matrix temp(*this);
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->clo; j++) {
      temp.data_m[i][j] /= k;
    }
  }
  return temp;
}
Matrix &Matrix::operator/=(double k) {
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->clo; j++) {
      this->data_m[i][j] /= k;
    }
  }
  return *this;
}

// Возвращает новую матрицу, полученную транспонированием текущей (this)
Matrix Matrix::transposed() const {
  Matrix temp(this->rows, this->clo, 0.0);
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->clo; j++) {
      temp.data_m[i][j] = this->data_m[j][i];
    }
  }
  return temp;
}

// Транспонирует текущую матрицу
void Matrix::transpose() {
  *this = this->transposed();
}

// Определитель
double Matrix::det() const {



}

// Обратная матрица
Matrix Matrix::inv() const {

}

// УМножение матрицы на вектор
Vector Matrix::operator*(const Vector &vec) const {
  Vector temp(this->clo, 0.0);
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->clo; j++) {
      temp[i] += data_m[i][j] * vec[j];
    }
  }
  return temp;
}

// Поэлементное сравнение
bool Matrix::operator==(const Matrix &rhs) const {
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->clo; j++) {
      if (this->data_m[i][j] != rhs.data_m[i][j])return false;
    }
  }
  return true;
}
bool Matrix::operator!=(const Matrix &rhs) const {
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->clo; j++) {
      if (this->data_m[i][j] == rhs.data_m[i][j])return false;
    }
  }
  return true;
}
}



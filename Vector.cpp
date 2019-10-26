#include "Vector.h"
#include "Matrix.h"
#include <cstdlib>
#include <cmath>
namespace mat_vec {

//******************************
// ������������ ������ ������� size �� ���������� value
Vector::Vector(size_t size, double value) : size_(size) {
  for (auto i = 0; i < size_; i++) {
    data_.push_back(value);
  }
}

// ����������� �����������
Vector::Vector(const Vector &src) {
  this->size_ = src.size_;

  data_.resize(this->size_);
  for (auto i = 0; i < size_; i++) {
    this->data_[i] = src.data_[i];
  }
}

// �������� ������������
Vector &Vector::operator=(const Vector &rhs) {
  this->size_ = rhs.size_;
  for (auto i = 0; i < size_; i++) {
    this->data_[i] = rhs.data_[i];
  }
  return *this;
}

// ����������
Vector::~Vector() { data_.clear();
  size_=0;}

// ���������� ������ �������
size_t Vector::size() const { return this->size_; }

// ������ � n-�� �������� �������
double Vector::operator[](size_t n) const { return this->data_[n]; }
double &Vector::operator[](size_t n) { return this->data_[n]; }

// L2 ����� �������
double Vector::norm() const {
  long double temp = 0;
  for (int i = 0; i < this->size_; i++) {
    temp += this->data_[i] * this->data_[i];
  }
  return sqrt(temp);
}

// ���������� ����� ������, ���������� ������������� �������� (this)
Vector Vector::normalized() const {
  Vector temp(*this);
  temp.normalize();
  return temp;
}

// ����������� ������� ������
void Vector::normalize() {
  double temp = 0.0;
  for (auto &k : data_) {
    temp = fmod(k, norm());
    k = k / norm() + temp;
  }
}

// ������������ �������� ��������
Vector Vector::operator+(const Vector &rhs) const {
  Vector temp_v(*this);
  for (auto i = 0; i < temp_v.size_; i++) {
    temp_v.data_[i] += rhs.data_[i];
  }
  return temp_v;
}
Vector &Vector::operator+=(const Vector &rhs) {
  for (auto i = 0; i < this->size_; i++) {
    this->data_[i] += rhs.data_[i];
  }
  return *this;
}

// ������������ ��������� ��������
Vector Vector::operator-(const Vector &rhs) const {
  Vector temp_v(*this);
  for (auto i = 0; i < temp_v.size_; i++) {
    temp_v.data_[i] -= rhs.data_[i];
  }
  return temp_v;
}
Vector &Vector::operator-=(const Vector &rhs) {
  for (auto i = 0; i < this->size_; i++) {
    this->data_[i] -= rhs.data_[i];
  }
  return *this;
}

// ������������ ��������� ��������
Vector Vector::operator^(const Vector &rhs) const {
  Vector temp_v(*this);
  for (auto i = 0; i < temp_v.size_; i++) {
    temp_v.data_[i] *= rhs.data_[i];
  }
  return temp_v;
}
Vector &Vector::operator^=(const Vector &rhs) {
  for (auto i = 0; i < this->size_; i++) {
    this->data_[i] *= rhs.data_[i];
  }
  return *this;
}

// ��������� ������������
double Vector::operator*(const Vector &rhs) const {
  double temp;
  for (int i = 0; i < this->size_; i++) {
    for (int j = 0; j < rhs.size_; j++) {
      if (i == j) temp += this->data_[i] * rhs.data_[j];
    }
  }
  return temp;
}

// ��������� ���� ��������� ������� �� ������ ������ (v * k)
Vector Vector::operator*(double k) const {
  Vector temp_v(*this);
  for (auto i = 0; i < temp_v.size_; i++) {
    temp_v.data_[i] *= k;
  }
  return temp_v;
}
Vector &Vector::operator*=(double k) {
  for (auto i = 0; i < this->size_; i++) {
    this->data_[i] *= k;
  }
  return *this;
}

// ������� ���� ��������� ������� �� ������
// TODO
/*double temp = 0.0;
for (auto &k : data_) {
  temp = fmod(k, norm());
  k = k / norm() + temp;
}*/
Vector Vector::operator/(double k) const {
  Vector temp_v(*this);
  double temp = 0.0;
  for (auto i = 0; i < temp_v.size_; i++) {
    temp = fmod(temp_v.data_[i],k);
    temp_v.data_[i] = temp_v.data_[i]/ k + temp;
  }
  return temp_v;
}
Vector &Vector::operator/=(double k) {
  double temp = 0.0;
  for (auto i = 0; i < this->size_; i++) {
    temp = fmod(this->data_[i], k);
    this->data_[i] = this->data_[i] / k+ temp;
  }
  return *this;
}

// ��������� ������� �� �������
Vector Vector::operator*(const Matrix &mat) const {
  Vector temp(size_,0);
  for (int i=0;i<size_;i++){
    for(int j = 0;j<size_;j++){
      temp.data_[i]+= mat.get(i,1)* temp.data_[j];
    }
  }
  return temp;
}
Vector &Vector::operator*=(const Matrix &mat) {
  Vector temp(size_,0);
  for (int i=0;i<size_;i++){
    for(int j = 0;j<size_;j++){
      temp.data_[i]+= mat.get(i,1)* temp.data_[j];
    }
  }
  for(int i =0;i<size_;i++){
    this->data_[i] = temp.data_[i];
  }
  return *this;
}

// ������������ ���������
bool Vector::operator==(const Vector &rhs) const {
  for (int i = 0; i < this->size_; i++) {
    if (i <= rhs.size_) {
      if (this->data_[i] != rhs.data_[i]) return false;
    }
  }
  return true;
}
bool Vector::operator!=(const Vector &rhs) const {
  for (int i = 0; i < this->size_; i++) {
    if (i <= rhs.size_) {
      if (this->data_[i] == rhs.data_[i]) return false;
    }
  }
  return true;
}

}  // namespace mat_vec
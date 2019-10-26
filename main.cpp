#define CATCH_CONFIG_MAIN
#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include <catch.hpp>

#define cycle(a) for(int i = 0; i < a; i++)
#define cycle_(a) for(int j = 0; j < a; j++)

const double e = 0.000000000001;

using namespace mat_vec;

TEST_CASE("Vector::Vector(size_t size, double value)")
{
    Vector vector(5, 5);
    REQUIRE(vector.size() == 5);
    cycle(5)
    {
        REQUIRE(vector[i] - 5.0 < e);
    }
}

TEST_CASE("Vector::Vector(const Vector &src)")
{
    Vector vector_src(5, 5);
    Vector vector(vector_src);
    REQUIRE(vector.size() == 5);
    cycle(5)
    {
        REQUIRE(vector[i] - 5.0 < e);
    }
}

TEST_CASE("Vector &Vector::operator=(const Vector &rhs)")
{
    Vector vector_src(5, 5);
    Vector vector = vector_src;
    REQUIRE(vector.size() == 5);
    cycle(5)
    {
        REQUIRE(vector[i] - 5.0 < e);
    }
}

TEST_CASE("size_t Vector::size() const")
{
    Vector vector(7);
    REQUIRE(vector.size() == 7);
}

TEST_CASE("double Vector::operator[](size_t n) const")
{
    Vector vector(5, 5);
    REQUIRE(vector[1] - 5.0 < e);
}

TEST_CASE("double &Vector::operator[](size_t n)")
{
    Vector vector(5, 5);
    vector[1] = 7;
    REQUIRE(vector[1] - 7 < e);
}

TEST_CASE("double Vector::norm() const")
{
    Vector vector(4, 5);
    REQUIRE(vector.norm() - 10 < e);
}

TEST_CASE("Vector Vector::normalized() const")
{
    Vector vector(4, 5);
    Vector vector_src(vector);
    vector = vector_src.normalized();
    cycle(4)
    {
        REQUIRE(vector[i] - 0.5 < e);
    }
}

TEST_CASE("void Vector::normalize()")
{
    Vector vector(4, 5);
    vector.normalize();
    cycle(4)
    {
        REQUIRE(vector[i] - 0.5 < e);
    }
}

TEST_CASE("Vector Vector::operator+(const Vector &rhs) const")
{
    Vector vector(4, 5);
    Vector _vector(4, 7);
    Vector __vector(_vector);
    __vector = _vector + vector;
    cycle(4)
    {
        REQUIRE(__vector[i] - 12 < e);
    }
}

TEST_CASE("Vector &Vector::operator+=(const Vector &rhs)")
{
    Vector vector(4, 5);
    Vector _vector(4, 7);
    _vector += vector;
    cycle(4)
    {
        REQUIRE(_vector[i] - 12 < e);
    }
}

TEST_CASE("Vector Vector::operator-(const Vector &rhs) const")
{
    Vector vector(4, 5);
    Vector _vector(4, 7);
    Vector __vector(_vector);
    __vector = vector - _vector;
    cycle(4)
    {
        REQUIRE(__vector[i] - 2 < e);
    }
}

TEST_CASE("Vector &Vector::operator-=(const Vector &rhs)")
{
    Vector vector(4, 5);
    Vector _vector(4, 7);
    vector = vector.operator-=(_vector);
    cycle(4)
    {
        REQUIRE(vector[i] - 2 < e);
    }
}

TEST_CASE("Vector Vector::operator^(const Vector &rhs) const")
{
    Vector vector(4, 5);
    Vector _vector(4, 2);
    Vector __vector(_vector);
    __vector = vector ^ _vector;
    cycle(4)
    {
        REQUIRE(__vector[i] - 10 < e);
    }
}

TEST_CASE("Vector &Vector::operator^=(const Vector &rhs)")
{
    Vector vector(4, 5);
    Vector _vector(4, 2);
    vector = _vector.operator^=(_vector);
    cycle(4)
    {
        REQUIRE(_vector[i] - 10 < e);
    }
}

TEST_CASE("double Vector::operator*(const Vector &rhs) const")
{
    Vector vector(4, 5);
    Vector _vector(4, 2);
    double result = vector.operator*(_vector);
    REQUIRE(result - 40 < e);
}

TEST_CASE("Vector Vector::operator*(double k) const")
{
    Vector vector(4, 5);
    Vector _vector(4, 2);
    vector = _vector * 5;
    cycle(4)
    {
        REQUIRE(vector[i] - 10 < e);
    }
}

TEST_CASE("Vector &Vector::operator*=(double k)")
{
    Vector vector(4, 2);
    vector *= 5;
    cycle(4)
    {
        REQUIRE(vector[i] - 10 < e);
    }
}

TEST_CASE("Vector mat_vec::operator*(double k, const Vector &v)")
{
    Vector vector(4, 5);
    Vector _vector(4, 2);
    vector = _vector.operator*(5);
    cycle(4)
    {
        REQUIRE(vector[i] - 10 < e);
    }
}

TEST_CASE("Vector Vector::operator/(double k) const")
{
    Vector vector(4, 6);
    Vector _vector(4, 2);
    _vector = vector / 2;
    cycle(4)
    {
        REQUIRE(_vector[i] - 3 < e);
    }
}

TEST_CASE("Vector &Vector::operator/=(double k)")
{
    Vector vector(4, 6);
    vector /= 2;
    cycle(4)
    {
        REQUIRE(vector[i] - 3 < e);
    }
}

TEST_CASE("bool Vector::operator==(const Vector &rhs) const")
{
    Vector vector(4, 5);
    Vector _vector(4, 3);
    Vector rhs(4, 5);
    REQUIRE(rhs == vector);
    REQUIRE(!(_vector == vector));
}

TEST_CASE("bool Vector::operator!=(const Vector &rhs) const")
{
    Vector vector(4, 5);
    Vector _vector(4, 5);
    Vector rhs(4, 4);
    REQUIRE(rhs.operator!=(vector) == vector.operator!=(rhs));
    REQUIRE(!(_vector.operator!=(vector) != vector.operator!=(_vector)));
}

TEST_CASE("Vector &Vector::operator*=(const Matrix &mat)")
{
    Matrix matrix(2, 3, 0);
    Vector vector(2);
    cycle(2)
    {
        vector[i] = i + 1;
    }
    vector *= matrix;
    REQUIRE(vector.size() == 2);
    REQUIRE(vector[0] - 9 < e);
    REQUIRE(vector[1] - 12 < e);
    REQUIRE(vector[2] - 15 < e);
}

TEST_CASE("Vector Vector::operator*(const Matrix &mat) const")
{
    Matrix matrix(2, 3, 0);
    Vector vector(2);
    cycle(2)
    {
        vector[i] = i + 1;
    }
    Vector _vector = vector * matrix;
    REQUIRE(_vector.size() == 3);
    REQUIRE(_vector[0] - 9 < e);
    REQUIRE(_vector[1] - 12 < e);
    REQUIRE(_vector[2] - 15 < e);
}
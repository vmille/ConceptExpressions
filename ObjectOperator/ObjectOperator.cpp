//
// Created by mille on 16-Nov-18.
//

#include "ObjectOperator.h"

Vector::Vector(std::size_t s) : _values(s) {}

Vector::Vector(std::initializer_list<double> init) : _values{init} {}

Vector & Vector::operator=(Vector const & rhs) {
    _values = rhs._values;
    return *this;
}

Vector Vector::operator+(Vector const & rhs) {
    assert(size() == rhs.size());
    Vector res(size());
    for (std::size_t i = 0; i < size(); ++i) {
        res[i] = this->operator[](i)+rhs[i];
    }
    return res;
}

Vector Vector::operator-() {
    Vector res(size());
    for (std::size_t i = 0; i < size(); ++i) {
        res[i] = -this->operator[](i);
    }
    return res;
}

double & Vector::operator[](std::size_t i) {
    return _values[i];
}

double const & Vector::operator[](std::size_t i) const {
    return _values[i];
}

std::size_t Vector::size() const {
    return _values.size();
}

double sum(Vector const & v) {
    double res{};
    for (std::size_t i = 0; i < v.size(); ++i) {
        res += v[i];
    }
    return res;
}

Vector operator*(double d, Vector const & rhs) {
    Vector res{rhs};
    for (std::size_t i = 0; i < res.size(); ++i) {
        res[i] = d*rhs[i];
    }
    return res;
}
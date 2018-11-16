//
// Created by mille on 16-Nov-18.
//

#include "VirtualObject.h"

#include <cassert>

AddVector::AddVector(VectorExpression const & lhs, VectorExpression const & rhs) : _lhs{lhs}, _rhs{rhs} { assert(_lhs.size() == _rhs.size()); }
double AddVector::operator[](std::size_t i) const { return _lhs[i]+_rhs[i]; }
std::size_t AddVector::size() const { return _lhs.size(); }
AddVector operator+(VectorExpression const & lhs, VectorExpression const & rhs) { return {lhs, rhs}; }

UnaryMinusVector::UnaryMinusVector(VectorExpression const & lhs) : _lhs{lhs} {}
double UnaryMinusVector::operator[](std::size_t i) const { return -_lhs[i]; }
std::size_t UnaryMinusVector::size() const { return _lhs.size(); }
UnaryMinusVector operator-(VectorExpression const & rhs) { return UnaryMinusVector(rhs); }

MultiplyScalar::MultiplyScalar(double scalar, VectorExpression const & rhs) : _scalar{scalar}, _rhs{rhs} {}
double MultiplyScalar::operator[](std::size_t i) const { return _scalar*_rhs[i]; }
std::size_t MultiplyScalar::size() const { return _rhs.size(); }
MultiplyScalar operator*(double scalar, VectorExpression const & rhs) { return MultiplyScalar(scalar, rhs); }

Vector::Vector(std::size_t i) : _values(i) {}
Vector::Vector(std::initializer_list<double> init) : _values{init} {}

Vector::Vector(VectorExpression const & exp) : _values(exp.size()) {
    for (std::size_t i = 0; i < _values.size(); ++i) {
        _values[i] = exp[i];
    }
}
Vector & Vector::operator=(VectorExpression const & exp) {
    _values.resize(exp.size());
    for (std::size_t i = 0; i < _values.size(); ++i) {
        _values[i] = exp[i];
    }
    return *this;
}
std::size_t Vector::size() const { return _values.size(); };
double Vector::operator[](std::size_t i) const { return _values[i]; };

double sum(VectorExpression const & exp) {
    double res{};
    for (std::size_t i = 0; i < exp.size(); ++i) {
        res += exp[i];
    }
    return res;
}

#ifndef CONCEPTEXPRESSIONS_TEMPLATEEXPRESSIONS_1_H
#define CONCEPTEXPRESSIONS_TEMPLATEEXPRESSIONS_1_H
#include <iostream>
#include <vector>
#include <cassert>

template <typename E>
struct VectorExpression {
    double operator[](size_t i) const { return static_cast<E const &>(*this)[i]; }
    size_t size() const { return static_cast<E const &>(*this).size(); }
};

template <typename E1, typename E2>
class AddVector : public VectorExpression<AddVector<E1, E2>> {
    E1 const & _u;
    E2 const & _v;
public:
    AddVector(E1 const & u, E2 const & v) : _u{u}, _v{v} { }
    double operator[](size_t i) const { return _u[i]+_v[i]; }
    size_t size() const { return _u.size(); }
};

template <typename E1, typename E2>
AddVector<E1, E2> operator+(E1 const & u, E2 const & v) {
    return AddVector<E1, E2>(u, v);
}

template <typename E1>
class UnaryMinusVector : public VectorExpression<UnaryMinusVector<E1>> {
    E1 const & _u;
public:
    explicit UnaryMinusVector(E1 const & u) : _u{u} {}
    double operator[](size_t i) const { return -_u[i]; }
    size_t size() const { return _u.size(); }
};

template <typename E1>
UnaryMinusVector<E1> operator-(E1 const & u) {
    return UnaryMinusVector<E1>(u);
}

template <typename E2>
class MultiplyScalar : public VectorExpression<MultiplyScalar<E2>> {
    double _scalar;
    E2 const & _v;
public:
    MultiplyScalar(double scalar, E2 const & v) : _scalar{scalar}, _v{v} { }
    double operator[](size_t i) const { return _scalar*_v[i]; }
    size_t size() const { return _v.size(); }
};

template <typename E2>
MultiplyScalar<E2> operator*(double scalar, E2 const & v) {
    return MultiplyScalar<E2>(scalar, v);
}

class Vector : public VectorExpression<Vector> {
    std::vector<double> _values;
public:
    double operator[](size_t i) const { return _values[i]; }
    size_t size() const { return _values.size(); }
    Vector(size_t n) : _values(n) {}
    // construct vector using initializer list
    Vector(std::initializer_list<double> init) : _values{init} {}

    // A Vec can be constructed from any VectorExpression, forcing its evaluation.
    template <typename E>
    explicit Vector(VectorExpression<E> const & exp) : _values(exp.size()) {
        for (size_t i = 0 ; i != exp.size() ; ++i) {
            _values[i] = exp[i];
        }
    }
};

template <typename E>
double sum(VectorExpression<E> const & exp) {
    double res{};
    for (size_t i = 0 ; i != exp.size() ; ++i) {
        res += exp[i];
    }
    return res;
}


#endif //CONCEPTEXPRESSIONS_TEMPLATEEXPRESSIONS_1_H

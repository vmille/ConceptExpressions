#ifndef CONCEPTEXPRESSIONS_TEMPLATEEXPRESSIONS_1_H
#define CONCEPTEXPRESSIONS_TEMPLATEEXPRESSIONS_1_H
#include <iostream>
#include <vector>
#include <cassert>

template <typename E>
class VectorEx {
public:
    double operator[](size_t i) const { return static_cast<E const &>(*this)[i]; }
    size_t size() const { return static_cast<E const &>(*this).size(); }
};

class Vector : public VectorEx<Vector> {
    std::vector<double> elems;
public:
    double operator[](size_t i) const { return elems[i]; }
    double & operator[](size_t i) { return elems[i]; }
    size_t size() const { return elems.size(); }
    Vector(size_t n) : elems(n) {}
    // construct vector using initializer list
    Vector(std::initializer_list<double> init) : elems{init} {}

    // A Vec can be constructed from any VectorEx, forcing its evaluation.
    template <typename E>
    explicit Vector(VectorEx<E> const & vec) : elems(vec.size()) {
        for (size_t i = 0 ; i != vec.size() ; ++i) {
            elems[i] = vec[i];
        }
    }
};

template <typename E1, typename E2>
class VectorSum : public VectorEx<VectorSum<E1, E2>> {
    E1 const & _u;
    E2 const & _v;
public:
    VectorSum(E1 const & u, E2 const & v) : _u(u), _v(v) { }
    double operator[](size_t i) const { return _u[i]+_v[i]; }
    size_t size() const { return _u.size(); }
};

template <typename E1, typename E2>
VectorSum<E1, E2> operator+(E1 const & u, E2 const & v) {
    return VectorSum<E1, E2>(u, v);
}
#endif //CONCEPTEXPRESSIONS_TEMPLATEEXPRESSIONS_1_H

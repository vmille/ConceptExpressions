//
// Created by mille on 22-Oct-18.
//

#ifndef PROTO_VECEXPRESSION_H
#define PROTO_VECEXPRESSION_H
#include <iostream>
#include <vector>
#include <cassert>

template <typename E>
struct ScalarExpression {
    explicit operator double() const {
        return static_cast<E const &>(*this)();
    }
};

template <typename E>
struct SumVec : ScalarExpression<SumVec<E>> {
    E const & _e;

    explicit SumVec(E const & e) : _e{e} {}

    double operator()() const {
        double res{};
        for (size_t i = 0; i < _e.size(); ++i) {
            res += _e[i];
        }
        return res;
    }
};

template <typename E>
SumVec<E> sum(E const & e) {
    return SumVec<E>(e);
}

template <typename E>
class VecExpression {
public:
    double operator[](size_t i) const { return static_cast<E const &>(*this)[i]; }
    double at(size_t i) const { return static_cast<E const &>(*this).at(i); }
    size_t size() const { return static_cast<E const &>(*this).size(); }
};

class Vec : public VecExpression<Vec> {
    std::vector<double> elems;
public:
    double operator[](size_t i) const { return elems[i]; }
    double & operator[](size_t i) { return elems[i]; }
    size_t size() const { return elems.size(); }
    Vec(size_t n) : elems(n) {}
    // construct vector using initializer list
    Vec(std::initializer_list<double> init) : elems{init} {}

    // A Vec can be constructed from any VecExpression, forcing its evaluation.
    template <typename E>
    explicit Vec(VecExpression<E> const & vec) : elems(vec.size()) {
        for (size_t i = 0 ; i != vec.size() ; ++i) {
            elems[i] = vec[i];
        }
    }
};

template <typename E1, typename E2>
class VecSum : public VecExpression<VecSum<E1, E2>> {
    E1 const & _u;
    E2 const & _v;
public:
    VecSum(E1 const & u, E2 const & v) : _u(u), _v(v) {
        assert(u.size() == v.size());
    }
    double operator[](size_t i) const { return _u[i]+_v[i]; }
    size_t size() const { return _v.size(); }
};


template <typename E1, typename E2>
VecSum<E1, E2> operator+(E1 const & u, E2 const & v) {
    return VecSum<E1, E2>(u, v);
}


void foo() {
    Vec v0 = {1.0, 2.0, 3.0};
    Vec v1 = {4.0, 5.0, 6.0};
    Vec v2 = {7.0, 8.0, 9.0};

    // Following assignment will call the ctor of Vec which accept type of
    // `VecExpression<E> const&`. Then expand the loop body to
    // a.elems[i] + b.elems[i] + c.elems[i]
    Vec sum_of_vec_type{v0+v1+v2};

    for (int i = 0 ; i < sum_of_vec_type.size() ; ++i) {
        std::cout << sum_of_vec_type[i] << std::endl;
    }
    double s{sum(v0+v1+v2)};
    std::cout << s << std::endl;
}
#endif //PROTO_VECEXPRESSION_H

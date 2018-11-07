//
// Created by mille on 06-Nov-18.
//

#ifndef PROTO_CONCEPTEXPRESSION_H
#define PROTO_CONCEPTEXPRESSION_H
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

//template <typename E>
//class VecExpression {
//public:
//    double operator[](size_t i) const { return static_cast<E const &>(*this)[i]; }
//    size_t size() const { return static_cast<E const &>(*this).size(); }
//};

template <typename T>
concept bool VecExpression = requires(T t) {
{t[int{}]}->double;
{t.size()}->size_t;
};

//class Vec {
//    std::vector<double> elems;
//public:
//    double operator[](size_t i) const { return elems[i]; }
//    double & operator[](size_t i) { return elems[i]; }
//    size_t size() const { return elems.size(); }
//    Vec(size_t n) : elems(n) {}
//    // construct vector using initializer list
//    Vec(std::initializer_list<double> init) : elems{init} {}
//
//    // A Vec can be constructed from any VecExpression, forcing its evaluation.
//    template <VecExpression E>
//    explicit Vec(E const & vec) : elems(vec.size()) {
//        for (size_t i = 0 ; i != vec.size() ; ++i) {
//            elems[i] = vec[i];
//        }
//    }
//};


template <typename T, typename... Tail>
bool all_equal(T const & t, Tail const &... tail) {
    return ((t == tail) && ...);
}

template <VecExpression... E1>
class VecSum {
    std::tuple<E1... const &> _operands;
public:
    VecSum(E1 const &... u) : _u(u...) {
        assert(all_equal(u.size()...));
    }

    double operator[](size_t i) const {
        return (_u[i]+...);
    }
    size_t size() const { return _v.size(); }
};


template <VecExpression E1, VecExpression E2>
VecSum<E1, E2> operator+(E1 const & u, E2 const & v) {
    return VecSum<E1, E2>(u, v);
}


#endif //PROTO_CONCEPTEXPRESSION_H

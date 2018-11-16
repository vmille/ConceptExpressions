#ifndef CONCEPTEXPRESSIONS_CONCEPTEXPRESSIONS_1_H
#define CONCEPTEXPRESSIONS_CONCEPTEXPRESSIONS_1_H
#include <iostream>
#include <vector>
#include <cassert>


template <typename T>
concept bool IndexedAccess = requires(T t, size_t i) {
    {t[i]}->double;
};

template <IndexedAccess E1, IndexedAccess E2>
class AddVector {
    E1 const & _u;
    E2 const & _v;
public:
    explicit AddVector(E1 const & u, E2 const & v) : _u{u}, _v{v} {}

    double operator[](size_t i) const {
        return _u[i]+_v[i];
    }
};

template <IndexedAccess E1, IndexedAccess E2>
AddVector<E1, E2> operator+(E1 const & u, E2 const & v) {
    return AddVector<E1, E2>(u, v);
}

#endif //CONCEPTEXPRESSIONS_CONCEPTEXPRESSIONS_1_H

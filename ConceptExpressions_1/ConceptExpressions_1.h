#ifndef CONCEPTEXPRESSIONS_CONCEPTEXPRESSIONS_1_H
#define CONCEPTEXPRESSIONS_CONCEPTEXPRESSIONS_1_H
#include <iostream>
#include <vector>
#include <cassert>


template <typename T>
concept bool IndexedAccess = requires(T t, size_t i) {
    {t[i]}->double;
};

template <typename T>
concept bool SizeMember = requires(T t) {
    {t.size()}->std::size_t;
};

template <typename T>
concept bool Sizeable = requires(T t) {
    {size(t)}->std::size_t;
};

template <typename T>
concept bool Reducable = Sizeable<T> && IndexedAccess<T>;

template <SizeMember T>
std::size_t size(T && t) {
    return t.size();
}

template <typename T, std::size_t N>
std::size_t size(T (&t)[N]) {
    return N;
}

template <IndexedAccess E1, IndexedAccess E2>
class Add {
    E1 const & _u;
    E2 const & _v;
public:
    explicit Add(E1 const & u, E2 const & v) : _u{u}, _v{v} { assert(_u.size() == _v.size()); }

    double operator[](size_t i) const {
        return _u[i]+_v[i];
    }

    std::size_t size() const { return _u.size(); }
};

template <IndexedAccess E1, IndexedAccess E2>
Add<E1, E2> operator+(E1 && u, E2 && v) {
    return Add<E1, E2>(u, v);
}

template <IndexedAccess E1>
class UnaryMinus {
    E1 const & _u;
public:
    explicit UnaryMinus(E1 const & u) : _u{u} {}

    double operator[](size_t i) const {
        return -_u[i];
    }

    std::size_t size() const { return _u.size(); }
};

template <IndexedAccess E1>
UnaryMinus<E1> operator-(E1 && u) {
    return UnaryMinus<E1>(u);
}

template <IndexedAccess E2>
class MultiplyScalar {
    double _scalar;
    E2 const & _v;
public:
    explicit MultiplyScalar(double scalar, E2 const & v) : _scalar{scalar}, _v{v} {}

    double operator[](size_t i) const {
        return _scalar*_v[i];
    }

    std::size_t size() const { return _v.size(); }
};

template <IndexedAccess E2>
MultiplyScalar<E2> operator*(double scalar, E2 && v) {
    return MultiplyScalar<E2>(scalar, v);
}

template <Reducable T>
double sum(T && t) {
    double res{};
    for (std::size_t i = 0; i < size(t); ++i) {
        res += t[i];
    }
    return res;
}

#endif //CONCEPTEXPRESSIONS_CONCEPTEXPRESSIONS_1_H

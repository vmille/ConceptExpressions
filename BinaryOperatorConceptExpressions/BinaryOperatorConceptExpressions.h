#ifndef CONCEPTEXPRESSIONS_BINARYOPERATORCONCEPTEXPRESSIONS_H
#define CONCEPTEXPRESSIONS_BINARYOPERATORCONCEPTEXPRESSIONS_H
#include <iostream>
#include <vector>
#include <cassert>

template <typename T>
concept bool IndexedAccess = requires(T t, size_t i) {
    {t[i]}->double;
};

template <typename TOps>
concept bool UnaryOperation = requires(double t) {
{TOps{}(t)}->double;
};

template <typename TOps>
concept bool BinaryOperation = requires(double t) {
    {TOps{}(t, t)}->double;
};

template <BinaryOperation TOp, IndexedAccess E1, IndexedAccess E2>
class BinaryVectorOperation {
    TOp _op;
    E1 const & _u;
    E2 const & _v;
public:
    explicit BinaryVectorOperation(E1 const & u, E2 const & v) : _op{}, _u{u}, _v{v} {}

    double operator[](size_t i) const {
        return _op(_u[i], _v[i]);
    }
};

template <UnaryOperation TOp, IndexedAccess E1>
class UnaryVectorOperation {
    TOp _op;
    E1 const & _u;
public:
    explicit UnaryVectorOperation(E1 const & u) : _op{}, _u{u} {}

    double operator[](size_t i) const {
        return _op(_u[i]);
    }
};

template <IndexedAccess E1, IndexedAccess E2>
auto operator+(E1 const & u, E2 const & v) {
    return BinaryVectorOperation<std::plus<double>, E1, E2>(u, v);
}

template <IndexedAccess E1, IndexedAccess E2>
auto operator-(E1 const & u, E2 const & v) {
    return BinaryVectorOperation<std::minus<double>, E1, E2>(u, v);
}

template <IndexedAccess E1, IndexedAccess E2>
auto operator*(E1 const & u, E2 const & v) {
    return BinaryVectorOperation<std::multiplies<double>, E1, E2>(u, v);
}

template <IndexedAccess E1, IndexedAccess E2>
auto operator/(E1 const & u, E2 const & v) {
    return BinaryVectorOperation<std::divides<double>, E1, E2>(u, v);
}

template <IndexedAccess E1>
auto operator-(E1 const & u) {
    return UnaryVectorOperation<std::negate<double>, E1>(u);
}

#endif //CONCEPTEXPRESSIONS_BINARYOPERATORCONCEPTEXPRESSIONS_H

#ifndef CONCEPTTEXPRESSIONS_TEMPLATEEXPRESSIONS_2_H
#define CONCEPTTEXPRESSIONS_TEMPLATEEXPRESSIONS_2_H

#include <vector>
#include <algorithm>
#include <iostream>

struct Add{};

template <typename E1, typename E2>
auto operator+(E1 && e1, E2 && e2) {
    return [&](auto visitor) { return visitor(Add{}, e1(visitor), e2(visitor));};
}

struct UnaryMinus{};

template <typename E1>
auto operator-(E1 && e1) {
    return [&](auto visitor) { return visitor(UnaryMinus{}, e1(visitor));};
}

struct MultiplyScalar{};

template <typename E2>
auto operator*(double scalar, E2 && e2) {
    return [&](auto visitor) { return visitor(MultiplyScalar{}, scalar, e2(visitor));};
}

struct Spread{};

template <typename E1>
auto spread(E1 & e1) {
    return [&](auto visitor) { return visitor(Spread{}, e1);};
}

struct evaluator {

    std::size_t _i;

    explicit evaluator(std::size_t i) : _i{i} {}

    template <typename E1, typename E2>
    auto operator()(Add, E1 e1, E2 e2) { return e1+e2; }

    template <typename E1>
    auto operator()(UnaryMinus, E1 e1) { return -e1; }

    template <typename E2>
    auto operator()(MultiplyScalar, double scalar, E2 e2) { return scalar*e2; }

    template <typename E1>
    auto operator()(Spread, E1 & e1) { return e1[_i]; }
};

struct size {
    template <typename E1>
    auto operator()(Spread, E1 & e1) { return e1.size(); }

    template <typename Tag, typename E1, typename E2>
    auto operator()(Tag, E1 e1, E2 e2) { return std::min(e1, e2); }

    template <typename E2>
    auto operator()(MultiplyScalar, double e1, E2 e2) { return e2; }

    template <typename Tag, typename E1>
    auto operator()(Tag, E1 e1) { return std::numeric_limits<size_t>::max(); }
};

template <typename Expression>
double sum(Expression && exp) {
    std::size_t size_expression = exp(size{});
    double res{};
    for(size_t i = 0; i < size_expression; ++i) {
        res += exp(evaluator{i});
    }
    return res;
}

class Vector {
    std::vector<double> _values;
public :
    Vector(std::initializer_list<double> init) : _values{init} {}
    double operator[](std::size_t i) { return _values.at(i); }
    std::size_t size() const { return _values.size(); }
};

#endif //CONCEPTTEXPRESSIONS_TEMPLATEEXPRESSIONS_2_H

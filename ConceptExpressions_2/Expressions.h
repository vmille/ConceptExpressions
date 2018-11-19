//
// Created by mille on 19-Nov-18.
//

#ifndef CONCEPTEXPRESSIONS_EXPRESSIONS_H
#define CONCEPTEXPRESSIONS_EXPRESSIONS_H

#include "Concepts.h"
#include <tuple>
#include <functional>

struct UnaryMinusTag {};
struct AddTag{};
struct MultiplyTag{};
struct SumTag{};

template <typename Operator, cExpression... Expressions>
struct Expression {
    using operator_t = Operator;
    using operands_t = std::tuple<Expressions const &...>;
    operands_t _expressions;

    Expression(Expressions const &... expressions) : _expressions{expressions...} {}

    template <unsigned N>
    std::tuple_element_t<N, operands_t> const & get() {
        return std::get<N>(this->_expressions);
    }
};

template <cExpression Operator, cExpression TExpression1>
using UnaryExpression = Expression<Operator, TExpression1>;

template <typename Operator, cExpression TExpression1, cExpression Expression2>
using BinaryExpression = Expression<Operator, TExpression1, Expression2>;

template <typename E1>
auto operator-(E1 && e1) {
    return UnaryExpression<UnaryMinusTag, E1>(std::forward<E1>(e1));
}

template <typename E1, typename E2>
auto operator+(E1 && e1, E2 && e2) {
    return BinaryExpression<AddTag, E1, E2>(std::forward<E1>(e1), std::forward<E2>(e2));
}

template <typename E1, typename E2>
auto operator*(E1 && e1, E2 && e2) {
    return BinaryExpression<MultiplyTag, E1, E2>(std::forward<E1>(e1), std::forward<E2>(e2));
}

template <typename E1>
auto sum(E1 && e1) {
    return UnaryExpression<SumTag, E1>(std::forward<E1>(e1));
}

#endif //CONCEPTEXPRESSIONS_EXPRESSIONS_H

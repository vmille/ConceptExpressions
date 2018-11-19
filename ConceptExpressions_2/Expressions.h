//
// Created by mille on 19-Nov-18.
//

#ifndef CONCEPTEXPRESSIONS_EXPRESSIONS_H
#define CONCEPTEXPRESSIONS_EXPRESSIONS_H

#include <tuple>
#include <functional>

template <unsigned N, typename T>
decltype(auto) get(T && t) {
    return t.template get<N>();
}

template <typename T>
concept bool cExpression = true;

template <typename T>
concept bool cUnaryExpression = cExpression<T> && requires(T t) {
    {get<0>(t)}
};

template <typename T>
concept bool cBinaryExpression = cExpression<T> && requires(T t) {
    {get<0>(t)}
    {get<1>(t)}
};

template <typename Operator, cExpression... Expressions>
struct Expression {
    using tag = Operator;
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

struct UnaryMinusTag{};

template <typename T>
concept bool cUnaryMinus = cUnaryExpression<T> && std::is_same<T, UnaryMinusTag>::value;

struct AddTag{};

template <typename T>
concept bool cAdd = cBinaryExpression<T> && std::is_same<T, AddTag>::value;

struct MultiplyTag{};

template <typename T>
concept bool cMultiply = cBinaryExpression<T> && std::is_same<T, MultiplyTag>::value;

struct SumTag{};

template <typename T>
concept bool cSum = cUnaryExpression<T> && std::is_same<T, SumTag>::value;

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

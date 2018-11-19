//
// Created by mille on 19-Nov-18.
//

#ifndef CONCEPTEXPRESSIONS_EVALUATOR_H
#define CONCEPTEXPRESSIONS_EVALUATOR_H

#include "Visitor.h"
#include "Expressions.h"
#include <cstddef>
#include <functional>

struct Evaluator {};

struct SizeTag{};

template <typename E1>
auto size(E1 && e1) {
    return UnaryExpression<SizeTag, E1>(std::forward<E1>(e1));
}

template <>
struct visitor<Evaluator, UnaryMinusTag> {
    static double run(TExpression const & exp, std::size_t i) {
        return -apply<Evaluator>(get<0>(exp), i)
    }
};

template <>
struct visitor<Evaluator, AddTag> {
    static double run(TExpression const & exp, std::size_t i) {
        return apply<Evaluator>(get<0>(exp), os) + apply<Evaluator>(get<1>(exp), i);
    }
};

template <>
struct visitor<Evaluator, MultiplyTag> {
    static double run(TExpression const & exp, std::size_t i) {
        return get<0>(exp) * apply<Evaluator>(get<1>(exp), i);
    }
};

template <typename T> requires Sizeable<T> && IndexedAccess<T>
struct visitor<Evaluator, T> {
    static std::size_t run(T const & array) {
        return array.size();
    }
};

template <>
struct visitor<Evaluator, SumTag> {
    static double run(TExpression const & exp) {
        double res{};
        for (std::size_t i = 0; i < get<0>(exp).size(); ++i) {
            res += apply<Evaluator>(get<0>(exp), i)
        }
        return res;
    }
};

#endif //CONCEPTEXPRESSIONS_EVALUATOR_H

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

template <>
struct visitor<Evaluator, UnaryMinusTag> {
    template <typename TExpression>
    static double run(TExpression const & exp, std::size_t i) {
        return -apply<Evaluator>(get<0>(exp), i);
    }
};

template <>
struct visitor<Evaluator, AddTag> {
    template <typename TExpression>
    static double run(TExpression const & exp, std::size_t i) {
        return apply<Evaluator>(get<0>(exp), i) + apply<Evaluator>(get<1>(exp), i);
    }
};

template <>
struct visitor<Evaluator, MultiplyTag> {
    template <typename TExpression>
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
    template <typename TExpression>
    static double run(TExpression const & exp) {
        double res{};
        for (std::size_t i = 0; i < visitor<Evaluator, SizeTag>::run(get<0>(exp)); ++i) {
            res += apply<Evaluator>(get<0>(exp), i)
        }
        return res;
    }
};

#endif //CONCEPTEXPRESSIONS_EVALUATOR_H

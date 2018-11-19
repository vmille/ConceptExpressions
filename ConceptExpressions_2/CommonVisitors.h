//
// Created by mille on 19-Nov-18.
//

#ifndef CONCEPTEXPRESSIONS_COMMONVISITORS_H
#define CONCEPTEXPRESSIONS_COMMONVISITORS_H

#include "Expressions.h"
#include "Visitor.h"
#include <limits>

struct SizeTag{};

template <typename E1>
auto size(E1 && e1) {
    return UnaryExpression<SizeTag, E1>(std::forward<E1>(e1));
}

template <typename TContext>
struct visitor<TContext, SizeTag> {
    template <cUnaryExpression TExpression>
    static std::size_t run(TExpression && exp) {
        return run(get<0>(exp));
    }

    template <cBinaryExpression TExpression>
    static std::size_t run(TExpression && exp) {
        return std::min(run(get<0>(exp)), run(get<1>(exp)));
    }

    template <cSizeable T>
    static std::size_t run(T && array) {
        return array.size();
    }

    template <cArithmetic T>
    static std::size_t run(T && other) {
        return std::numeric_limits<std::size_t>::max();
    }
};


#endif //CONCEPTEXPRESSIONS_COMMONVISITORS_H

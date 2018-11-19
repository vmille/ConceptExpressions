//
// Created by mille on 19-Nov-18.
//

#ifndef CONCEPTEXPRESSIONS_COMMONVISITORS_H
#define CONCEPTEXPRESSIONS_COMMONVISITORS_H

#include "Visitor.h"

struct SizeTag{};

template <typename T>
concept bool cSize = cUnaryExpression<T> && std::is_same<T, SizeTag>::value;

template <typename E1>
auto size(E1 && e1) {
    return UnaryExpression<SizeTag, E1>(std::forward<E1>(e1));
}

template <typename TContext>
struct visitor<TContext, SizeTag> {
    template <cUnaryExpression TExpression>
    static std::size_t run(TExpression const & exp) {
        return run(get<0>(exp);
    }

    template <cBinaryExpression TExpression>
    static std::size_t run(TExpression const & exp) {
        return std::min(run(get<0>(exp)), run(get<1>(exp)));
    }

    template <typename T> requires Sizeable<T>
    static std::size_t run(T const & array) {
        return array.size();
    }

    template <typename T>
    static std::size_t run(T const & other) {
        return std::numeric_limit<std::size_t>::max();
    }
};


#endif //CONCEPTEXPRESSIONS_COMMONVISITORS_H

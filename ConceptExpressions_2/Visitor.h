//
// Created by mille on 19-Nov-18.
//

#ifndef CONCEPTEXPRESSIONS_VISITOR_H
#define CONCEPTEXPRESSIONS_VISITOR_H

#include <type_traits>
#include <functional>

template <typename Context, cExpression TExpression>
struct visitor {
    static_assert(sizeof(Context) == -1, "Need to specialize visitor");
};

template <typename Context, typename TExpression, typename... Operands>
auto apply(TExpression const & expression, Operands &&... operands) {
    return visitor<Context, std::decay_t<TExpression>>::run(std::forward<TExpression>(expression), std::forward<Operands...>(operands...));
}

#endif //CONCEPTEXPRESSIONS_VISITOR_H

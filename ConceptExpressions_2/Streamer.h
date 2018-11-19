//
// Created by mille on 19-Nov-18.
//

#ifndef CONCEPTEXPRESSIONS_STREAMER_H
#define CONCEPTEXPRESSIONS_STREAMER_H

#include "Array.h"
#include "Visitor.h"
#include "Expressions.h"
#include "CommonVisitors.h"
#include <iostream>

struct Streamer {};

template <typename T>
struct SSymbol {};

template <>
struct SSymbol<UnaryMinusTag> {
    static constexpr char value = '-';
};

template <>
struct SSymbol<AddTag> {
    static constexpr char value = '+';
};

template <>
struct SSymbol<MultiplyTag> {
    static constexpr char value = '*';
};

template <typename T>
constexpr auto Symbol() {
    return SSymbol<typename T::tag>::value;
}

template <typename T>
concept bool cSymbol = requires {
    {Symbol<T>>()}
};

template <>
struct visitor<Streamer, SumTag> {
    template <cUnaryExpression TExpression>
    static void run(TExpression && exp, std::ostream & os) {
        os << "sum(" << apply<Streamer>(get<0>(std::forward<TExpression>(exp)), os) << ')';
    }
};

template <typename TTag>
struct visitor<Streamer, TTag> {
    template <typename TExpression> requires cUnaryExpression<TExpression> && cSymbol<TExpression>
    static void run(TExpression && exp, std::ostream & os) {
        os << Symbol<TExpression>();
        os << apply<Streamer>(get<0>(std::forward<TExpression>(exp)), os);
    }

    template <typename TExpression> requires cBinaryExpression<TExpression> && cSymbol<TExpression>
    static void run(TExpression && exp, std::ostream & os) {
        os << '(';
        os << apply<Streamer>(get<0>(std::forward<TExpression>(exp)), os);
        os << Symbol<TExpression>();
        os << apply<Streamer>(get<0>(std::forward<TExpression>(exp)), os);
        os << ')';
    }

    template <cReduceable TReduce>
    static void run(TReduce && array, std::ostream & os) {
        os << '[';
        bool is_first = true;
        for (unsigned i = 0; i < array.size(); ++i) {
            if (is_first) {
                is_first = false;
            }
            else {
                os << ',';
            }
            os << array[i];
        }
        os << ']';
    }

    template <cArithmetic T>
    static void run(T && scalar, std::ostream & os) {
        os << scalar;
    }
};


#endif //CONCEPTEXPRESSIONS_STREAMER_H

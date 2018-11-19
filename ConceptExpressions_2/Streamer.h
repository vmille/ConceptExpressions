//
// Created by mille on 19-Nov-18.
//

#ifndef CONCEPTEXPRESSIONS_STREAMER_H
#define CONCEPTEXPRESSIONS_STREAMER_H

#include "Array.h"
#include "Visitor.h"
#include "Expressions.h"
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

template <>
struct SSymbol<SumTag> {
    static constexpr char const * value = "sum:";
};

template <>
struct SSymbol<SumTag> {
    static constexpr char const * value = "size:";
};

template <typename T>
constexpr auto Symbol() {
    return SSymbol<typename T::tag>::value;
}

template <typename T> requires Sizeable<T> && IndexedAccess<T>
struct visitor<Streamer, T> {
    static void run(T const & array, std::ostream & os) {
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
};

template <cUnaryExpression TExpression>
struct visitor<Streamer, TExpression> {
    static void run(TExpression const & exp, std::ostream & os) {
        os << Symbol<TExpression>();
        os << apply<Streamer>(get<0>(exp), os);
    }
};

template <cBinaryExpression TExpression>
struct visitor<Streamer, TExpression> {
    static void run(TExpression const & exp, std::ostream & os) {
        os << '(';
        os << apply<Streamer>(get<0>(exp), os);
        os << Symbol<TExpression>();
        os << apply<Streamer>(get<0>(exp), os);
        os << ')';
    }
};

#endif //CONCEPTEXPRESSIONS_STREAMER_H

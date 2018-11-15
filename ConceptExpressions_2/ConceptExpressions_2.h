#ifndef CONCEPTEXPRESSIONS_CONCEPTEXPRESSIONS_2_H
#define CONCEPTEXPRESSIONS_CONCEPTEXPRESSIONS_2_H
#include <iostream>
#include <vector>
#include <cassert>
#include <type_traits>
#include <tuple>

template <typename T>
concept bool cExpression = requires {
    typename T::operator_t;
    typename T::operands_t;
};

template <typename T>
concept bool cUnaryExpression = cExpression<T> && requires {
    std::tuple_size<typename T::operands_t>::value == 1;
};

template <typename T>
concept bool cBinaryExpression = cExpression<T> && requires {
    std::tuple_size<typename T::operands_t>::value == 2;
};

template <typename T>
concept bool cLiteral = cUnaryExpression<T> && requires {
    std::is_integral<typename std::tuple_element<0, typename T::operands_t>::type>::value;
};

struct Evaluator{};
struct Streamer{};

template <size_t N>
struct Toto {
    double values[N];
    explicit Toto(std::initializer_list<double> list) {
        auto it = list.begin();

        for (unsigned i = 0; i<N; ++i) values[i]=*(it++);
    }
};

template <typename TOperator, typename... TOperands>
struct Expression {
    using operator_t = TOperator;
    using operands_t = std::tuple<TOperands...>;

    explicit Expression(TOperands const &... operands) : _operands{operands...} {}

    operands_t _operands;

    template <std::size_t N>
    auto get() {
        return std::get<N>(_operands);
    }
};

template <char Symbol>
struct Operator_Tag {
    static constexpr char symbol{Symbol};
};

template <typename TExpression>
constexpr char Symbol() {
    return TExpression::operator_t::symbol;
}

using Add_Tag = Operator_Tag<'+'>;

template <typename E1, typename E2>
cBinaryExpression operator+(E1 const & e1, E2 const & e2) {
    return Expression<Add_Tag, E1, E2>(e1, e2);
}

using Unary_Minus_Tag = Operator_Tag<'-'>;

template <typename E1>
cUnaryExpression operator-(E1 const & e1) {
    return Expression<Unary_Minus_Tag, E1>(e1);
}

template <typename TContext, cExpression TExpression>
struct visitor {
    static_assert(sizeof(TContext) == -1, "Visitor is not implemented");
};

template <typename TContext, cExpression TExpression, typename... TOperands>
static auto apply(TExpression const & ex, TOperands &&... operands) {
    return visitor<TContext, TExpression>::run(ex, operands...);
}

template <std::size_t N>
struct visitor<Streamer, Toto<N>> {
    static void run(Toto<N> const & a, std::ostream & os)  {
        os << "Array of size " << N;
    }
};

template <cLiteral TLiteral>
struct visitor<Streamer, TLiteral> {
    static void run(TLiteral const & exp, std::ostream & os)  {
        os << exp;
    }
};

template <cUnaryExpression TExpression1>
struct visitor<Streamer, TExpression1> {
    static void run(TExpression1 const & exp, std::ostream & os)  {
        os << Symbol<TExpression1>();
//        apply<Streamer>(exp.get<0>(), os);
    }
};

template <cBinaryExpression TExpression2>
struct visitor<Streamer, TExpression2> {
    static void run(cBinaryExpression const & exp, std::ostream & os)  {
        os << '(';
//        apply<Streamer>(exp.get<0>(), os);
        os << Symbol<TExpression2>();
//        apply<Streamer>(exp.get<1>(), os);
        os << ')';
    }
};

#endif //CONCEPTEXPRESSIONS_CONCEPTEXPRESSIONS_H

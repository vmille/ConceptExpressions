#ifndef CONCEPTTEXPRESSIONS_TEMPLATEEXPRESSIONS_2_H
#define CONCEPTTEXPRESSIONS_TEMPLATEEXPRESSIONS_2_H

#include <cstddef>
#include <tuple>
#include <functional>

namespace detail {
    template <typename F, typename Tuple, std::size_t... I>
    constexpr decltype(auto) apply_impl(F && f, Tuple && t, std::index_sequence<I...>) {
        return f(std::get<I>(std::forward<Tuple>(t))...);
    }
}

template <typename F, typename Tuple>
constexpr decltype(auto) apply(F && f, Tuple && t) {
    return detail::apply_impl(std::forward<F>(f), std::forward<Tuple>(t), std::make_index_sequence<std::tuple_size<std::remove_reference_t<Tuple>>::value>{});
}


template <size_t N>
class Array {
private:
    double values[N];

public:
    double operator[](size_t i) const { return values[i]; }

    double & operator[](size_t i) { return values[i]; }

    double eval(size_t i) const { return values[i]; }

    Array() : values{0} { }

    Array(std::initializer_list<double> list) {
        auto it = list.begin();
        for (size_t i = 0; i < N; ++i) {
            values[i] = *(it++);
        }
    }

    Array(Array<N> const & array) {
        for (size_t i = 0; i < N; ++i) {
            values[i] = array.values[i];
        }
    }

    template <typename TExpression>
    Array(TExpression const & expression) {
        for (size_t i = 0 ; i < N ; ++i) {
            values[i] = expression.eval(i);
        }
    }

    Array<N> & operator=(Array<N> const & array) {
        for (size_t i = 0 ; i < N ; ++i) {
            values[i] = array.values[i];
        }
        return *this;
    }

    template <typename TExpression>
    Array<N> & operator=(TExpression const & expression) {
        for (size_t i = 0 ; i < N ; ++i) {
            values[i] = expression.eval(i);
        }
        return *this;
    }
};

template <typename TOperator, typename... TOperands>
struct Expression {
    std::tuple<TOperands const & ...> _operands;

    Expression(TOperands const & ... operands) : _operands{operands...} {}

    double eval(size_t i) const { return TOperator::eval(i, _operands); }
};

struct AdditionOperator {
    template <typename... TOperands>
    static double eval(size_t i, std::tuple<TOperands...> const & operands) {
        return apply([i](auto... items) { return (items.eval(i)+...); }, operands);
    }
};

template <typename TOperand1, typename TOperand2>
Expression<AdditionOperator, TOperand1, TOperand2> operator+(TOperand1 && operand1, TOperand2 && operand2) {
    return {std::forward<TOperand1>(operand1), std::forward<TOperand2>(operand2)};
}

struct MultiplicationOperator {
    template <typename... TOperands>
    static double eval(size_t i, std::tuple<TOperands...> const & operands) {
        return apply([i](auto... items) { return (items.eval(i)*...); }, operands);
    }
};

template <typename TOperand1, typename TOperand2>
Expression<MultiplicationOperator, TOperand1, TOperand2> operator*(TOperand1 && operand1, TOperand2 && operand2) {
    return {std::forward<TOperand1>(operand1), std::forward<TOperand2>(operand2)};
}

struct UnaryMinusOperator {
    template <typename TOperand>
    static double eval(size_t i, std::tuple <TOperand> const & operand) {
        return -std::get<0>(operand).eval(i);
    }
};

template <typename TOperand>
Expression<UnaryMinusOperator, TOperand> operator-(TOperand && operand) {
    return {std::forward<TOperand>(operand)};
}

#endif //CONCEPTTEXPRESSIONS_TEMPLATEEXPRESSIONS_2_H

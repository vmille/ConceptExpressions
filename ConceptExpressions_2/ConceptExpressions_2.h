#ifndef CONCEPTEXPRESSIONS_CONCEPTEXPRESSIONS_2_H
#define CONCEPTEXPRESSIONS_CONCEPTEXPRESSIONS_2_H
#include <iostream>
#include <vector>
#include <cassert>

template <typename TOperator, typename TOperand>
concept bool UnaryOperator = require(TOperand d) {
    {TOperator{}(d)}->TOperand;
};

template <typename TOperator, typename TOperand>
concept bool BinaryOperator = require(TOperand d) {
    {TOperator{}(d, d)}->TOperand;
};

template <typename Tag, typename TOperator, typename... TOperands>
struct Expression {
    std::tuple<TOperands const &...> _operands;

    Expression(TOperands const &... operands) : _operands{std::forward<TOperands...>(operands...)} {}

    double eval(size_t i) const { return TOperator::eval(i, _operands); }
};

struct Add_Tag{};
template <typename TOp, typename E1, typename E2>
using Add = Expression<Add_Tag, TOp, E1, E2>;

template <

//
//struct Add_Tag{};
//template <typename E1, typename E2>
//auto add(E1 && e1, E2 && e2) {
//    return [&](auto && visitor) {visitor(Add_Tag{}, std::forward<E1>(e1), std::forward<E2>(e2))};
//}
//
//struct Visitor {
//    auto operator()(Add_Tag, auto && e1, auto && e2) {return e1+e2;}
//};
//
//template <typename TOperand1, typename TOperand2>
//Expression<Add_Tag, std::decay<TOperand1>::type, std::decay<TOperand2>::type> operator+(TOperand1 && op1, TOperand2 && op2) {
//    return {std::forward<TOperand1>(op1), std::forward<TOperand2>(op2)};
//}
//
//struct Multiply_Tag{};
//
//template <typename TOperand1, typename TOperand2>
//Expression<Multiply_Tag, std::decay<TOperand1>::type, std::decay<TOperand2>::type> operator*(TOperand1 && op1, TOperand2 && op2) {
//    return {std::forward<TOperand1>(op1), std::forward<TOperand2>(op2)};
//}
//
//struct UnaryMinus_Tag{};
//
//template <typename TOperand1>
//Expression<UnaryMinus_Tag, std::decay<TOperand1>::type> operator-(TOperand1 && op1) {
//    return {std::forward<TOperand1>(op1)};
//}

#endif //CONCEPTEXPRESSIONS_CONCEPTEXPRESSIONS_H

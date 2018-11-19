//
// Created by mille on 19-Nov-18.
//

#ifndef CONCEPTEXPRESSIONS_CONCEPTS_H
#define CONCEPTEXPRESSIONS_CONCEPTS_H


template <unsigned N, typename T>
decltype(auto) get(T && t) {
    return t.template get<N>();
}

template <typename T>
concept bool cExpression = requires {
    typename T::operator_t;
    typename T::operands_t;
};

template <typename T1, typename T2>
concept bool cSame = std::is_same<T1, T2>::value;

template <typename T>
concept bool cUnaryExpression = cExpression<T> && requires(T t) {
    {get<0>(t)}
};

template <typename T>
concept bool cBinaryExpression = cExpression<T> && requires(T t) {
    {get<0>(t)}
    {get<1>(t)}
};

template <typename T>
concept bool cArithmetic = std::is_arithmetic<T>::value;

template <typename T>
concept bool cSizeable = requires(T t) {
    {t.size()}->std::size_t;
};

template <typename T>
concept bool cIndexedAccess = requires(T t, std::size_t i) {
    {t[i]}->double;
};

template <typename T>
concept bool cReduceable = cSizeable<T> && cIndexedAccess<T>;

#endif //CONCEPTEXPRESSIONS_CONCEPTS_H

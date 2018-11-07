//
// Created by mille on 06-Nov-18.
//

#ifndef PROTO_REPLACE_CONTAINER_H
#define PROTO_REPLACE_CONTAINER_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

#include "VecExpression.h"
#include <typeinfo>
#include <map>



template <typename Callable, typename Content>
struct Reduce {
    Callable _c;
    Content _result;

    explicit Reduce(Callable && c, Content && init) : _c{c}, _result{init} {}

    template <typename T>
    auto operator()(T const & t) {
        return _result += _c(_result, t);
    }

    explicit operator Content() const {
        return _result;
    }
};

template <typename Callable, typename Init>
Init reduce(Callable c, Init init) {
    return Reduce<decltype(c), decltype(init)>{std::move(c), std::move(init)};
}

template <typename E1, typename Callable, typename Init>
Init operator|(E1 const & e1, Reduce<Callable, Init> && tr) {
    using result_type = decltype(tr(*begin(e1)));
    return 0;
}

template <typename E>
struct RangeExpression {
    auto begin() const {
        return begin(static_cast<E const &>(*this));
    }

    auto end() const {
        return end(static_cast<E const &>(*this));
    }
};

template <typename Callable>
struct Transform {
    Callable _c;

    explicit Transform(Callable && c) : _c{c} {}

    template <typename T>
    auto operator()(T const & t) {
        return _c(t);
    }
};

template <typename Callable>
auto tranformed(Callable c) {
    return Transform<decltype(c)>{std::move(c)};
}

template <typename E1, typename Callable>
auto operator|(E1 const & e1, Transform<Callable> && tr) {
    using result_type = decltype(tr(*begin(e1)));
    return 0;
}

template <typename, typename, typename = void>
struct replace_value_type {};

template <typename, typename = void>
struct has_key_type : std::false_type {};

template <typename> struct void_{using type = void;};

template <typename T>
struct has_key_type<T, typename void_<typename T::key_type>::type> : std::true_type {};


template <typename TRKey, typename TRValue, template <typename, typename...> class C, typename TKey, typename TValue, typename... TTails>
struct replace_value_type<std::pair<TRKey, TRValue>, C<TKey, TValue, TTails...>, std::enable_if_t<has_key_type<C<TKey, TValue, TTails...>>::value>> {
    using type = C<TRKey, TRValue>;
};

template <typename TReplace, template <typename, typename...> class C, typename TFirst, typename... TTails>
struct replace_value_type<TReplace, C<TFirst, TTails...>, std::enable_if_t<!has_key_type<C<TFirst, TTails...>>::value>> {
    using type = C<TReplace>;
};

template <typename Container>
struct Transform_Iterator {

    auto operator++(int) const {

    }
};

template <typename Container, typename Expression>
auto operator|(Container const & c, Expression && e) {
    using result_type = replace_value_type<decltype(e(*begin(c))), std::remove_cv_t<decltype(c)>>;
    return result_type{};
}

void bar() {
        std::vector<double> res;
        std::cout << typeid(std::vector<double>).name() << std::endl;
        std::cout << typeid(std::vector<int>).name() << std::endl;

        std::cout << has_key_type<std::map<int, int>>::value << std::endl;
        std::cout << has_key_type<std::vector<std::pair<int, int>>>::value << std::endl;

        std::cout << typeid(replace_value_type<int, std::vector<double>>::type).name() << std::endl;
        std::cout << std::is_same<std::vector<std::string>, replace_value_type<std::string, std::vector<double>>::type>::value << std::endl;

        std::cout << typeid(replace_value_type<std::pair<std::string, std::string>, std::map<int, int>>::type).name() << std::endl;
        std::cout << std::is_same<std::map<std::string, std::string>, replace_value_type<std::pair<std::string, std::string>, std::map<int, int>>::type>::value << std::endl;



//    std::vector<double> vec;
//    auto res = vec | tranformed([](auto c){return std::to_string(c);});
//    std::cout << typeid(decltype(res)).name() << std::endl;

}

#endif //PROTO_REPLACE_CONTAINER_H

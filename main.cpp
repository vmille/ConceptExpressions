//#include "ConceptExpression.h"

#include <vector>
#include <iostream>
#include <tuple>
#include <cassert>
#include <functional>

namespace detail {
    template <class F, class Tuple, std::size_t... I>
    constexpr decltype(auto) apply_impl(F && f, Tuple&& t, std::index_sequence<I...>) {
        return f(std::get<I>(std::forward<Tuple>(t))...);
    }
}  // namespace detail

template <class F, class Tuple>
constexpr decltype(auto) apply(F&& f, Tuple&& t) {
    return detail::apply_impl(
            std::forward<F>(f), std::forward<Tuple>(t),
            std::make_index_sequence<std::tuple_size<std::remove_reference_t<Tuple>>::value>{});
}

template <typename T>
concept bool AccessIndexed = requires(T t) {
    {t[int{}]}->double;
};

template <typename T>
concept bool Sizeable = requires(T t) {
    {t.size()}->size_t;
};

template <typename T, typename... Tail>
bool all_equal(T const & t, Tail const &... tail) {
    return ((t == tail) &&...);
}

template <AccessIndexed... E1>
class VecSum {
    std::tuple<E1 const &...> _operands;
public:
    explicit VecSum(E1 const &... u) : _operands(u...) {
        assert(apply([](auto... items){return all_equal(items.size()...);}, this->_operands));
    }

    double operator[](size_t i) const {
        return apply([i](auto... items){return (items[i]+...);}, this->_operands);
    }
};

template <AccessIndexed... E1>
auto add(E1 const &... e) {
    return VecSum<E1...>{e...};
}

int main() {
    std::vector<double> v0 = {1.0, 2.0, 3.0};
    std::vector<double> v1 = {4.0, 5.0, 6.0};
    std::vector<double> v2 = {7.0, 8.0, 9.0};

    auto res = add(v0, v1, v2);
    std::cout << res[0] << ";" << res[1] << ";" << res[2] << ";" << std::endl;
//    Vec v0 = {1.0, 2.0, 3.0};
//    Vec v1 = {4.0, 5.0, 6.0};
//    Vec v2 = {7.0, 8.0, 9.0};
//
//    // Following assignment will call the ctor of Vec which accept type of
//    // `VecExpression<E> const&`. Then expand the loop body to
//    // a.elems[i] + b.elems[i] + c.elems[i]
//    Vec sum_of_vec_type{v0+v1+v2};
//
//    for (int i = 0 ; i < sum_of_vec_type.size() ; ++i) {
//        std::cout << sum_of_vec_type[i] << std::endl;
//    }
//    double s{sum(v0+v1+v2)};
//    std::cout << s << std::endl;
}
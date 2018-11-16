#include "ConceptExpressions_2.h"

#include <vector>
#include <iostream>
#include <tuple>
#include <cassert>
#include <functional>

template <typename T>
concept bool cBase = true;

template <typename T>
concept bool cDerived1 = cBase<T> && requires(T t) {
    {t.var1()}
};

template <typename T>
concept bool cDerived2 = cBase<T> && requires(T t) {
    {t.var2()}
};

struct Derived1 {
    void var1() {
        std::cout << "var1" << std::endl;
    };
};

struct Derived2 {
    void var2() {
        std::cout << "var2" << std::endl;
    };
};

template <cBase T>
struct Wrapper {

};

template <cDerived1 T>
struct Wrapper<T> {
    void display() {
        T{}.var1();
    }
};

template <cDerived2 T>
struct Wrapper<T> {
    void display() {
        T{}.var2();
    }
};

int main() {

    Wrapper<Derived1> d1;
    d1.display();

    Wrapper<Derived2> d2;
    d2.display();

//    double tab[3] = {1.0, 2.0, 3.0};
//    std::vector<double> v1{4.0, 5.0, 6.0};
//    std::vector<double> v2{7.0, 8.0, 9.0};

//    Toto<3> tab{1.0, 2.0, 3.0};
//    Toto<3> v1{4.0, 5.0, 6.0};
//    Toto<3> v2{7.0, 8.0, 9.0};
//
//    apply<Streamer>(tab+v1+v2, std::cout);
//    auto op{tab+v1+v2};
//    auto result{op};

//    for (int i = 0; i < 3; ++i) {
//        std::cout << "result[" << i << "] : " << result[i] << std::endl;
//    }
}
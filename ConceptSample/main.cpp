#include <iostream>

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
}
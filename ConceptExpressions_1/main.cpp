#include "ConceptExpressions_1.h"

#include <vector>
#include <iostream>
#include <tuple>
#include <cassert>
#include <functional>

template <std::size_t N>
struct Array {
    double _values[N];
    double & operator[](std::size_t i) {
        assert(i < N);
        return _values[i];
    }
    std::size_t size() const {
        return N;
    }
};

int main() {
    double a = 2.0;
    double b = 7.0;
    std::vector<double> X{1.0, 2.0, 3.0, 4.0};
    Array<4> Y{5.0, 6.0, 7.0, 8.0};
    std::array<double, 4> Z{9.0, 10.0, 11.0, 12.0};
    double res = sum(-X+a*Y+b*Z);
    std::cout << "Result : " << res << std::endl;
}
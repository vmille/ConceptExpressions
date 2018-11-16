#include <array>
#include <iostream>

int main() {
    std::array<double, 4> a{1.0, 2.0, 3.0, 4.0};
    std::array<double, 4> b{5.0, 6.0, 7.0, 8.0};
    std::array<double, 4> c{9.0, 10.0, 11.0, 12.0};
    double res{};

    for (size_t i = 0; i < a.size(); ++i) {
        res += -a[i]+b[i]*c[i];
    }
    std::cout << "Result : " << res << std::endl;
}
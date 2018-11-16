#include <array>
#include <iostream>

int main() {
    double a = 2.0;
    double b = 7.0;
    std::array<double, 4> X{1.0, 2.0, 3.0, 4.0};
    std::array<double, 4> Y{5.0, 6.0, 7.0, 8.0};
    std::array<double, 4> Z{9.0, 10.0, 11.0, 12.0};
    double res{};

    for (size_t i = 0; i < X.size(); ++i) {
        res += -X[i]+a*Y[i]+b*Z[i];
    }
    std::cout << "Result : " << res << std::endl;
}
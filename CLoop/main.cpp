#include <array>
#include <iostream>

int main() {
    double a = 2.0;
    double b = 7.0;
    double X[4]{1.0, 2.0, 3.0, 4.0};
    double Y[4]{5.0, 6.0, 7.0, 8.0};
    double Z[4]{9.0, 10.0, 11.0, 12.0};
    double res = 0;

    for (size_t i = 0; i < 4; ++i) {
        res += -X[i]+a*Y[i]+b*Z[i];
    }
    std::cout << "Result : " << res << std::endl;
}

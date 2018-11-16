#include "ObjectOperator.h"

#include <iostream>

int main() {
    Vector a{1.0, 2.0, 3.0, 4.0};
    Vector b{5.0, 6.0, 7.0, 8.0};
    Vector c{9.0, 10.0, 11.0, 12.0};
    double res = sum(-a+b*c);
    std::cout << "Result : " << res << std::endl;
}
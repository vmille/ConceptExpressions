#include "VirtualObject.h"

#include <iostream>

int main() {
    double a = 2.0;
    double b = 7.0;
    Vector X{1.0, 2.0, 3.0, 4.0};
    Vector Y{5.0, 6.0, 7.0, 8.0};
    Vector Z{9.0, 10.0, 11.0, 12.0};
    double res = sum(-X+a*Y+b*Z);
    std::cout << "Result : " << res << std::endl;
}
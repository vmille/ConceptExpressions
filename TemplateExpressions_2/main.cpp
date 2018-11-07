#include "TemplateExpressions_2.h"

#include <vector>
#include <iostream>
#include <tuple>
#include <cassert>
#include <functional>

int main() {
    Array<5> a{ 1, 2, 3, 4, 5};
    Array<5> b{ 6, 7, 8, 9,10};
    Array<5> c{11,12,13,14,15};

    Array<5> e = -a+b*c;

//    std::cout << e << std::endl;

    std::cout << -a[0]+b[0]*c[0] << " "
              << -a[1]+b[1]*c[1] << " "
              << -a[2]+b[2]*c[2] << " "
              << -a[3]+b[3]*c[3] << " "
              << -a[4]+b[4]*c[4] << std::endl;
}
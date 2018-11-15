#include "ConceptExpressions_2.h"

#include <vector>
#include <iostream>
#include <tuple>
#include <cassert>
#include <functional>

int main() {
//    double tab[3] = {1.0, 2.0, 3.0};
//    std::vector<double> v1{4.0, 5.0, 6.0};
//    std::vector<double> v2{7.0, 8.0, 9.0};

    Toto<3> tab{1.0, 2.0, 3.0};
    Toto<3> v1{4.0, 5.0, 6.0};
    Toto<3> v2{7.0, 8.0, 9.0};

    apply<Streamer>(-tab+v1+v2, std::cout);
//    auto op{tab+v1+v2};
//    auto result{op};

//    for (int i = 0; i < 3; ++i) {
//        std::cout << "result[" << i << "] : " << result[i] << std::endl;
//    }
}
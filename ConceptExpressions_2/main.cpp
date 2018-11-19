#include "Expressions.h"
#include "Array.h"
#include "Streamer.h"
#include "Evaluator.h"

#include <vector>
#include <array>


int main() {

    double a = 2.0;
    double b = 7.0;
    std::vector<double> X{1.0, 2.0, 3.0, 4.0};
    Array<4> Y{5.0, 6.0, 7.0, 8.0};
    std::array<double, 4> Z{9.0, 10.0, 11.0, 12.0};

    apply<Streamer>(sum(-X+a*Y+b*Z), std::cout);
    double res = apply<Evaluator>(sum(-X+a*Y+b*Z));

    std::cout << "Result : " << res << std::endl;

}
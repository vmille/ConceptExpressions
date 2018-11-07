#include "TemplateExpressions.h"

int main() {
    Vector v0{1.0, 2.0, 3.0};
    Vector v1{4.0, 5.0, 6.0};
    Vector v2{7.0, 8.0, 9.0};

    // Following assignment will call the ctor of Vec which accept type of
    // `VecExpression<E> const&`. Then expand the loop body to
    // a.elems[i] + b.elems[i] + c.elems[i]
    auto op = v0+v1+v2;
    Vector result{op};
    for (int i = 0; i < result.size(); ++i) {
        std::cout << "result[" << i << "] : " << result[i] << std::endl;
    }
}
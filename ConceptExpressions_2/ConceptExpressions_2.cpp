//
// Created by mille on 17-Nov-18.
//

#include "ConceptExpressions_2.h"

template <typename column_t>
struct row;

template<int f>
struct column {
    static constexpr int flags = f;
};

template <std::size_t column_index>
struct row<column<column_index>> {
    static constexpr double d{4.5};

};

void foo() {
//    std::cout << row<column<4>>::d << std::endl;
}

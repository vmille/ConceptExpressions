//
// Created by mille on 19-Nov-18.
//

#ifndef CONCEPTEXPRESSIONS_ARRAY_H
#define CONCEPTEXPRESSIONS_ARRAY_H

#include <cstddef>

template <std::size_t N>
struct Array {
    double _values[N];
    double & operator[](unsigned i) {
        return _values[i];
    }
    double const & operator[](unsigned i) const {
        return _values[i];
    }
    static constexpr std::size_t size() {
        return N;
    }
};

#endif //CONCEPTEXPRESSIONS_ARRAY_H

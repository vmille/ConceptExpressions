#ifndef CONCEPTEXPRESSIONS_OBJECTOPERATOR_H
#define CONCEPTEXPRESSIONS_OBJECTOPERATOR_H

#include <vector>
#include <cassert>

class Vector {
    std::vector<double> _values;
public:
    Vector(std::size_t s);
    explicit Vector(std::initializer_list<double> init);
    ~Vector() = default;
    Vector const & operator=(Vector const & rhs);
    Vector operator+(Vector const & rhs);
    Vector operator*(Vector const & rhs);
    Vector operator-();
    double & operator[](std::size_t i);
    double const & operator[](std::size_t i) const;
    std::size_t size() const;
};

double sum(Vector const & v) {
    double res{};
    for (std::size_t i = 0; i < v.size(); ++i) {
        res += v[i];
    }
    return res;
}

#endif //CONCEPTEXPRESSIONS_OBJECTOPERATOR_H

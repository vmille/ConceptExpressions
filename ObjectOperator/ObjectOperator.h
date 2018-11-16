#ifndef CONCEPTEXPRESSIONS_OBJECTOPERATOR_H
#define CONCEPTEXPRESSIONS_OBJECTOPERATOR_H

#include <vector>
#include <cassert>

class Vector {
    std::vector<double> _values;
public:
    explicit Vector(std::size_t s);
    Vector(std::initializer_list<double> init);
    ~Vector() = default;
    Vector & operator=(Vector const & rhs);
    Vector operator+(Vector const & rhs);
    Vector operator-();
    double & operator[](std::size_t i);
    double const & operator[](std::size_t i) const;
    std::size_t size() const;
};

double sum(Vector const & v);

Vector operator*(double d, Vector const & rhs);

#endif //CONCEPTEXPRESSIONS_OBJECTOPERATOR_H

//
// Created by mille on 16-Nov-18.
//

#ifndef CONCEPTEXPRESSIONS_VIRTUALOBJECT_H
#define CONCEPTEXPRESSIONS_VIRTUALOBJECT_H

#include <vector>

struct VectorExpression {
    virtual double operator[](std::size_t i) const = 0;
    virtual std::size_t size() const = 0;
};

class AddVector : public VectorExpression {
    VectorExpression const & _lhs;
    VectorExpression const & _rhs;
public:
    AddVector(VectorExpression const & lhs, VectorExpression const & rhs);
    double operator[](std::size_t i) const override;
    std::size_t size() const override;
};

AddVector operator+(VectorExpression const & lhs, VectorExpression const & rhs);

class UnaryMinusVector : public VectorExpression {
    VectorExpression const & _lhs;
public:
    explicit UnaryMinusVector(VectorExpression const & lhs);
    double operator[](std::size_t i) const override;
    std::size_t size() const override;
};

UnaryMinusVector operator-(VectorExpression const & lhs);

class MultiplyScalar : public VectorExpression {
    double _scalar;
    VectorExpression const & _rhs;
public:
    explicit MultiplyScalar(double scalar, VectorExpression const & rhs);
    double operator[](std::size_t i) const override;
    std::size_t size() const override;
};

MultiplyScalar operator*(double scalar, VectorExpression const & rhs);

class Vector : public VectorExpression {
    std::vector<double> _values;
public:
    explicit Vector(std::size_t i);

    explicit Vector(VectorExpression const & exp);
    Vector(std::initializer_list<double> init);
    ~Vector() = default;
    Vector & operator=(VectorExpression const & exp);
    std::size_t size() const override;
    double operator[](std::size_t i) const override;
};

double sum(VectorExpression const & v);


#endif //CONCEPTEXPRESSIONS_VIRTUALOBJECT_H

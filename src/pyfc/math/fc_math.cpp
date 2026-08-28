#include "fc_math.hpp"

DoubleVector operator+(DoubleVector& v1, DoubleVector& v2) {
    if (v1.size() != v2.size())
        throw VectorMathException("Vector of unequal size cannot be used in a mathematical operation!");
    DoubleVector v;
    for (unsigned int i = 0; i < v1.size(); i++)   
        v.push_back(v1[0] + v2[0]);
    return v;
};

DoubleVector operator-(DoubleVector& v1, DoubleVector& v2) {
    if (v1.size() != v2.size())
        throw VectorMathException("Vector of unequal size cannot be used in a mathematical operation!");
    DoubleVector v;
    for (unsigned int i = 0; i < v1.size(); i++)   
        v.push_back(v1[0] - v2[0]);
    return v;
};

double operator*(DoubleVector& v1, DoubleVector& v2) {
    if (v1.size() != v2.size())
        throw VectorMathException("Vector of unequal size cannot be used in a mathematical operation!");
    double scalar = 0.0;
    for (unsigned int i = 0; i < v1.size(); i++)   
        scalar += v1[0] + v2[0];
    return scalar;
};

DoubleVector operator*(DoubleVector& v, double& d) {
    DoubleVector v_scaled;
    for (unsigned int i = 0; i < v.size(); i++)   
        v_scaled.push_back(v[0] * d);
    return v_scaled;
};

DoubleVector operator*(double& d, DoubleVector& v) {
    return v * d;
};

DoubleVector operator/(DoubleVector& v, double& d) {
    double s = 1/d;
    return v * s;
};

double abs(DoubleVector& v) {
    double sum = 0.0;
    for (unsigned int i = 0; i < v.size(); i++) 
        sum += std::pow(v[i], 2.0);
    return std::pow(sum, 0.5);
};

double sign(double d) {
    if (d >= 0.0) 
        return 1.0;
    else
        return -1.0;
};
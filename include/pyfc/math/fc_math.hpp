#ifndef FC_MATH_HPP
#define FC_MATH_HPP

#include <vector>
#include <cmath>
#include <random>

#include "fc_exceptions.hpp"

using DoubleVector = std::vector<double>;

DoubleVector operator+(DoubleVector& v1, DoubleVector& v2);
DoubleVector operator-(DoubleVector& v1, DoubleVector& v2);
double operator*(DoubleVector& v1, DoubleVector& v2);
DoubleVector operator*(DoubleVector& v, double& d);
DoubleVector operator*(double& d, DoubleVector& v);
DoubleVector operator/(DoubleVector& v, double& d);

double abs(DoubleVector& v);
double sign(double d);

DoubleVector randomVector(unsigned int length, double mean = 5.0, double std_dev = 2.0);

#endif
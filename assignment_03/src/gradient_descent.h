
#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H
#include "common.h"
GDResult gradientDescent(const vector<double>& c, double x, double rate,
                         double tolerance, int maxIterations);
#endif


#include "common.h"
#include <cmath>

GDResult gradientDescent(const vector<double>& c, double x, double rate,
                         double tolerance, int maxIterations) {
    GDResult result;
    result.degree = (int)c.size() - 1;
    result.iterations = 0;
    result.converged = false;

    for (int i = 1; i <= maxIterations; i++) {
        double derivative = 0.0;
        double power = 1.0;

        for (int j = 1; j < (int)c.size(); j++) {
            derivative += j * c[j] * power;
            power *= x;
        }

        if (fabs(derivative) <= tolerance) {
            result.converged = true;
            result.iterations = i - 1;
            break;
        }

        x -= rate * derivative;
        result.iterations = i;
    }

    double fx = 0.0;
    double power = 1.0;

    for (double value : c) {
        fx += value * power;
        power *= x;
    }

    result.x = x;
    result.fx = fx;

    return result;
}

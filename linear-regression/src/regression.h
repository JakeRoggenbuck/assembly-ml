#ifndef REGRESSION_H
#define REGRESSION_H

#include <stdlib.h>

struct DataFrame {
    double *y;
    double *x;
    size_t size;
};

struct LinearComponents {
    double slope;
    double b;
};

double squared_error(struct DataFrame *dataf, double(f)(double));

double mean_squared_error(struct DataFrame *dataf, double(f)(double));

struct LinearComponents *gradient_descent(struct DataFrame *dataf, double slope,
                                          double b, double learning_rate);

struct LinearComponents *regression(struct DataFrame *dataf, int epochs,
                                    double learning_rate, int verbose);

#endif // REGRESSION_H

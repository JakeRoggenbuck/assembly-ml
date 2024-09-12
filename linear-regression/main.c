#include <stdlib.h>

struct DataFrame {
    double *y;
    double *x;
    size_t size;
};

struct GradientVector {
    double slope_gradient;
    double b_gradient;
};

double squared_error(struct DataFrame *dataf, double(f)(double)) {
    double error = 0.0;

    for (int i = 0; i < dataf->size; i++) {
        double delta = (dataf->y[i] - f(dataf->x[i]));
        error += delta * delta;
    }

    return error;
}

double mean_squared_error(struct DataFrame *dataf, double(f)(double)) {
    return squared_error(dataf, f) / (double)(dataf->size);
}

struct GradientVector *gradient_descent(struct DataFrame *dataf, double slope,
                                        double b, double learning_rate) {
    double slope_gradient = 0.0;
    double b_gradient = 0.0;

    for (int i = 0; i < dataf->size; i++) {
        double a = (dataf->y[i] - (slope * dataf->x[i] + b));

        slope_gradient += -(2.0 / dataf->size) * dataf->x[i] * a;
        b_gradient += -(2.0 / dataf->size) * a;
    }

    struct GradientVector *g = malloc(sizeof(struct GradientVector));
    g->slope_gradient = slope - slope_gradient * learning_rate;
    g->b_gradient = b - b_gradient * learning_rate;

    return g;
}

#include <stdio.h>
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

struct LinearComponents *gradient_descent(struct DataFrame *dataf, double slope,
                                          double b, double learning_rate) {
    struct LinearComponents *g = malloc(sizeof(struct LinearComponents));

    double slope_gradient = 0.0;
    double b_gradient = 0.0;

    for (int i = 0; i < dataf->size; i++) {
        double a = (dataf->y[i] - (slope * dataf->x[i] + b));

        slope_gradient += -(2.0 / dataf->size) * dataf->x[i] * a;
        b_gradient += -(2.0 / dataf->size) * a;
    }

    g->slope = slope - slope_gradient * learning_rate;
    g->b = b - b_gradient * learning_rate;

    return g;
}

struct LinearComponents *regression(struct DataFrame *dataf, int epochs,
                                    double learning_rate, int verbose) {
    struct LinearComponents *l;

    double slope = 0.0;
    double b = 0.0;

    if (verbose) {
        for (int epoch = 0; epoch < epochs; epoch++) {
            l = gradient_descent(dataf, slope, b, learning_rate);
            if (epoch % 1000 == 0) {
                printf("Epoch [%i]: %f(x) + %f\n", epoch, slope, b);
            }

            slope = l->slope;
            b = l->b;
        }

    } else {
        for (int epoch = 0; epoch < epochs; epoch++) {
            l = gradient_descent(dataf, slope, b, learning_rate);

            slope = l->slope;
            b = l->b;
        }
    }

    return l;
}

#include <stdlib.h>

struct DataFrame {
    double *y;
    double *x;
    size_t size;
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

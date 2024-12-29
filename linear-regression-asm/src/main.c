#include "regression.h"
#include <assert.h>
#include <stdio.h>

double linear_function(double x) { return 5.0 * x + 2.0; }

int tests() {
    struct DataFrame dataf;

    dataf.size = 1;

    dataf.x = malloc(dataf.size * sizeof(double));
    dataf.y = malloc(dataf.size * sizeof(double));

    if (dataf.x == NULL) {
        fprintf(stderr, "Malloc failed.\n");
        exit(1);
    }

    if (dataf.y == NULL) {
        fprintf(stderr, "Malloc failed.\n");
        exit(1);
    }

    for (int i = 0; i < dataf.size; i++) {
        dataf.x[i] = (double)i;
        dataf.y[i] = 5.0 * dataf.x[i] + 2.0;
    }

    double se = r_squared_error(&dataf, linear_function);
    printf("%f\n", se);
    assert(se == 0.0);

    /*double mse = r_mean_squared_error(&dataf, linear_function);*/
    /*assert(mse == 0.0);*/
    /**/
    /*struct LinearComponents *components =*/
    /*    r_gradient_descent(&dataf, 0.0, 0.0, 0.001);*/
    /**/
    /*assert(components->slope != 0.0);*/
    /*assert(components->b != 0.0);*/
    /**/
    /*struct LinearComponents *regression_result =*/
    /*    r_regression(&dataf, 10000, 0.001, 1);*/
    /**/
    /*assert(regression_result->slope > 4.9 && regression_result->slope
     * < 5.1);*/
    /*assert(regression_result->b > 1.9 && regression_result->b < 2.1);*/
    /**/
    /*free(dataf.x);*/
    /*free(dataf.y);*/
    /**/
    /*free(components);*/
    /*free(regression_result);*/

    return 0;
}

int main() {
    tests();
    return 0;
}

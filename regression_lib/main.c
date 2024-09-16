#include "/usr/include/python3.12/Python.h"

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

double r_squared_error(struct DataFrame *dataf, double(f)(double));

double r_mean_squared_error(struct DataFrame *dataf, double(f)(double));

struct LinearComponents *r_gradient_descent(struct DataFrame *dataf,
                                            double slope, double b,
                                            double learning_rate);

struct LinearComponents *r_regression(struct DataFrame *dataf, int epochs,
                                      double learning_rate);

double r_squared_error(struct DataFrame *dataf, double(f)(double)) {
    double error = 0.0;

    for (int i = 0; i < dataf->size; i++) {
        double delta = (dataf->y[i] - f(dataf->x[i]));
        error += delta * delta;
    }

    return error;
}

double r_mean_squared_error(struct DataFrame *dataf, double(f)(double)) {
    return r_squared_error(dataf, f) / (double)(dataf->size);
}

struct LinearComponents *r_gradient_descent(struct DataFrame *dataf,
                                            double slope, double b,
                                            double learning_rate) {
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

struct LinearComponents *r_regression(struct DataFrame *dataf, int epochs,
                                      double learning_rate) {
    struct LinearComponents *l;

    double slope = 0.0;
    double b = 0.0;

    for (int epoch = 0; epoch < epochs; epoch++) {
        l = r_gradient_descent(dataf, slope, b, learning_rate);

        slope = l->slope;
        b = l->b;
    }

    return l;
}

static PyObject *regression(PyObject *self, PyObject *args) {
    PyObject *list1, *list2;
    int epoch;
    double learning_rate;

    if (!PyArg_ParseTuple(args, "O!O!id", &PyList_Type, &list1, &PyList_Type,
                          &list2, &epoch, &learning_rate)) {
        return NULL;
    }

    Py_ssize_t size1 = PyList_Size(list1);
    Py_ssize_t size2 = PyList_Size(list2);

    if (size1 != size2) {
        PyErr_SetString(PyExc_ValueError,
                        "Both lists must have the same length");
        return NULL;
    }

    PyObject *result_list = PyList_New(2);
    if (!result_list) {
        return NULL;
    }

    // Create dataframe
    struct DataFrame dataf;

    dataf.size = size1;
    dataf.x = malloc(dataf.size * sizeof(double));
    dataf.y = malloc(dataf.size * sizeof(double));

    for (Py_ssize_t i = 0; i < size1; i++) {
        PyObject *item1 = PyList_GetItem(list1, i);
        PyObject *item2 = PyList_GetItem(list2, i);

        if (!PyFloat_Check(item1) || !PyFloat_Check(item2)) {
            PyErr_SetString(PyExc_TypeError,
                            "Both lists must contain floats (doubles)");
            free(dataf.x);
            free(dataf.y);
            return NULL;
        }

        double a = PyFloat_AsDouble(item1);
        double b = PyFloat_AsDouble(item2);

        // Populate dataframe
        dataf.x[i] = a;
        dataf.y[i] = b;
    }

    // Run the regression
    struct LinearComponents *regression_result =
        r_regression(&dataf, epoch, learning_rate);

    PyObject *slope = PyFloat_FromDouble(regression_result->slope);
    PyObject *b = PyFloat_FromDouble(regression_result->b);

    // Create the result [slope, b]
    PyList_SetItem(result_list, 0, slope);
    PyList_SetItem(result_list, 1, b);

    free(dataf.x);
    free(dataf.y);
    free(regression_result);

    return result_list;
}

static PyMethodDef RegressionMethod[] = {
    {"regression_lib", regression, METH_VARARGS,
     "Python interface for C linear regression"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef regressionmodule = {
    PyModuleDef_HEAD_INIT, "regression_lib",
    "Python interface for C linear regression", -1, RegressionMethod};

PyMODINIT_FUNC PyInit_regression_lib(void) {
    return PyModule_Create(&regressionmodule);
}

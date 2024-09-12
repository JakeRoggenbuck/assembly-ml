#include "/usr/include/python3.12/Python.h"

static PyObject *add_one(PyObject *self, PyObject *args) {
    long int a;

    if (!PyArg_ParseTuple(args, "l", &a)) {
        return NULL;
    }

    a += 1;
    return PyLong_FromLong(a);
}

static PyMethodDef AddOneMethods[] = {
    {"add_one", add_one, METH_VARARGS,
     "Python interface for adding 1 as a function"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef addonemodule = {
    PyModuleDef_HEAD_INIT, "add_one",
    "Python interface for adding 1 as a function", -1, AddOneMethods};

PyMODINIT_FUNC PyInit_add_one(void) { return PyModule_Create(&addonemodule); }

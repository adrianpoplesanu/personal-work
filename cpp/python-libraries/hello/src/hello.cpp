#include <Python.h>

static PyObject* helloworld(PyObject* self, PyObject* args) {
    printf("Hello World Adrian\n");
    return Py_None;
}

static PyMethodDef myMethods[] = {
    { "helloworld", helloworld, METH_NOARGS, "Prints Hello World" },
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef myModule = {
    PyModuleDef_HEAD_INIT,
    "hello",
    "Hello World Test Module",
    -1,
    myMethods
};

PyMODINIT_FUNC PyInit_hello(void) {
    return PyModule_Create(&myModule);
}


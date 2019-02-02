/* example.c This is the code that PyMongo would write to integrate with libmongocrypt. */

#include <Python.h>
#include <stdint.h>
#include "mongocrypt.h"

void py_send_fn(void* ctx, const uint8_t* in, int to_send) {
    PyObject *stream = (PyObject*) ctx;
    PyObject_CallMethod(stream, "send", "y#", in, to_send);
}

void py_recv_fn(void* ctx, int to_recv, uint8_t* out) {
    char* buf;
    PyObject *stream = (PyObject*) ctx;
    PyObject* response = PyObject_CallMethod(stream, "recv", "i", to_recv);
    if (!response || !PyBytes_Check(response)) {
        PyErr_SetString(PyExc_TypeError, "returned value not bytes");
        return;
    }

    buf = PyBytes_AsString (response);
    memcpy (out, buf, to_recv);
    Py_DECREF (response);
}

static PyObject *py_encrypt(PyObject *dummy, PyObject *args) {
    PyObject *stream = NULL;
    mongocrypt_stream_t wrapped_stream;

    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "arg must be object");
        return NULL;
    }

    if (!PyObject_HasAttrString(stream, "send") || !PyObject_HasAttrString(stream, "recv")) {
        PyErr_SetString(PyExc_TypeError, "arg must have 'send' and 'recv' methods");
        return NULL;
    }

    wrapped_stream.send = py_send_fn;
    wrapped_stream.recv = py_recv_fn;
    wrapped_stream.ctx = stream;
    wrapped_stream.x = 123;

    mongocrypt_encrypt (&wrapped_stream);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef ExampleMethods[] = {
    {"encrypt", py_encrypt, METH_VARARGS, "Test creating a wrapper around a socket."},
    {NULL, NULL, 0, NULL} /* Sentinel */
};

static struct PyModuleDef examplemodule = {
    PyModuleDef_HEAD_INIT,
    "example", /* name of module */
    NULL,      /* module documentation, may be NULL */
    -1,        /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    ExampleMethods};

PyMODINIT_FUNC
PyInit_example(void) {
    return PyModule_Create(&examplemodule);
}
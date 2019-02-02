/* pymongocrypt.c
 * A bit of the integration that pymongo would need to write.
 */

#include <Python.h>
#include <stdint.h>
#include "mongocrypt.h"

/* callback for socket send. */
void py_send_fn(void *ctx, const uint8_t *in, int to_send)
{
    PyObject *stream = (PyObject *)ctx;
    PyObject_CallMethod(stream, "send", "y#", in, to_send);
}

/* callback for socket recv. */
void py_recv_fn(void *ctx, int to_recv, uint8_t *out)
{
    char *buf;
    PyObject *stream = (PyObject *)ctx;
    PyObject *response = PyObject_CallMethod(stream, "recv", "i", to_recv);
    if (!response || !PyBytes_Check(response))
    {
        PyErr_SetString(PyExc_TypeError, "returned value not bytes");
        return;
    }

    buf = PyBytes_AsString(response);
    memcpy(out, buf, to_recv);
    Py_DECREF(response);
}

/* wrapper around libmongocrypt's encrypt function. */
static PyObject *py_encrypt(PyObject *dummy, PyObject *args)
{
    PyObject *stream = NULL;
    mongocrypt_stream_t wrapped_stream;

    if (!PyArg_ParseTuple(args, "O", &stream))
    {
        PyErr_SetString(PyExc_TypeError, "arg must be object");
        return NULL;
    }

    if (!PyObject_HasAttrString(stream, "send") || !PyObject_HasAttrString(stream, "recv"))
    {
        PyErr_SetString(PyExc_TypeError, "arg must have 'send' and 'recv' methods");
        return NULL;
    }

    wrapped_stream.send = py_send_fn;
    wrapped_stream.recv = py_recv_fn;
    wrapped_stream.ctx = stream;

    mongocrypt_encrypt(&wrapped_stream);

    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pymongocrypt_methods[] = {
    {"encrypt", py_encrypt, METH_VARARGS, "Test creating a wrapper around a socket."},
    {NULL, NULL, 0, NULL} /* Sentinel. */
};

static struct PyModuleDef pymongocrypt_module = {PyModuleDef_HEAD_INIT, "pymongocrypt", NULL, -1, pymongocrypt_methods};

PyMODINIT_FUNC
PyInit_pymongocrypt(void)
{
    return PyModule_Create(&pymongocrypt_module);
}
#include <Python.h>
#include <numpy/arrayobject.h>
#include "core/core.h"

#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))

struct module_state {
    PyObject* error;
};

PyDoc_STRVAR(hist_base__doc__,
"hist_base(fn, out, outr, outg, outb)\n\n"
"Generates Histogram\n\n"
"Arguments:\n"
"        fn {str} -- path to png file\n"
"        out {numpy.ndarray} -- output\n"
"        outr {numpy.ndarray} -- output\n"
"        outg {numpy.ndarray} -- output\n"
"        outb {numpy.ndarray} -- output\n"
);

static PyObject* hist_base(PyObject* self, PyObject* args) {
    const char *fn;
    unsigned int **out_array_data_ptr, *out_data_ptr;
    NpyIter *out_iter;
    NpyIter_IterNextFunc *out_iter_next;
    PyObject *out_array, *outr_array, *outg_array, *outb_array;
    if (!PyArg_ParseTuple(args, "sO!O!O!O!",
                          &fn,
                          &PyArray_Type,
                          &out_array,
                          &PyArray_Type,
                          &outr_array,
                          &PyArray_Type,
                          &outg_array,
                          &PyArray_Type,
                          &outb_array)) {
        return NULL;
    }

    unsigned int hist[256], histr[256], histg[256], histb[256];
    int ret = core_hist(fn, hist, histr, histg, histb);
    if (ret) {
        switch (ret) {
        case 1:
            PyErr_SetString(PyExc_RuntimeError, "Histogram failure: NULL PTR");
            return NULL;
        case 2:
            PyErr_SetString(PyExc_RuntimeError, "Histogram failure: FILE IO");
            return NULL;
        case 3:
            PyErr_SetString(PyExc_RuntimeError, "Histogram failure: INVALID PNG");
            return NULL;
        }

    }

    if (!(out_iter = NpyIter_New((PyArrayObject*)out_array, NPY_ITER_READWRITE,
                                 NPY_KEEPORDER,
                                 NPY_NO_CASTING, NULL))) {
        return NULL;
    }
    if (!(out_iter_next = NpyIter_GetIterNext(out_iter, NULL))) {
        NpyIter_Deallocate(out_iter);
        return NULL;
    }
    out_array_data_ptr = (unsigned int**)NpyIter_GetDataPtrArray(out_iter);
    out_data_ptr = hist;
    do {
        **(out_array_data_ptr) = *(out_data_ptr++);
    } while (out_iter_next(out_iter));
    NpyIter_Deallocate(out_iter);

    if (!(out_iter = NpyIter_New((PyArrayObject*)outr_array, NPY_ITER_READWRITE,
                                 NPY_KEEPORDER,
                                 NPY_NO_CASTING, NULL))) {
        return NULL;
    }
    if (!(out_iter_next = NpyIter_GetIterNext(out_iter, NULL))) {
        NpyIter_Deallocate(out_iter);
        return NULL;
    }
    out_array_data_ptr = (unsigned int**)NpyIter_GetDataPtrArray(out_iter);
    out_data_ptr = histr;
    do {
        **(out_array_data_ptr) = *(out_data_ptr++);
    } while (out_iter_next(out_iter));
    NpyIter_Deallocate(out_iter);

    if (!(out_iter = NpyIter_New((PyArrayObject*)outg_array, NPY_ITER_READWRITE,
                                 NPY_KEEPORDER,
                                 NPY_NO_CASTING, NULL))) {
        return NULL;
    }
    if (!(out_iter_next = NpyIter_GetIterNext(out_iter, NULL))) {
        NpyIter_Deallocate(out_iter);
        return NULL;
    }
    out_array_data_ptr = (unsigned int**)NpyIter_GetDataPtrArray(out_iter);
    out_data_ptr = histg;
    do {
        **(out_array_data_ptr) = *(out_data_ptr++);
    } while (out_iter_next(out_iter));
    NpyIter_Deallocate(out_iter);

    if (!(out_iter = NpyIter_New((PyArrayObject*)outb_array, NPY_ITER_READWRITE,
                                 NPY_KEEPORDER,
                                 NPY_NO_CASTING, NULL))) {
        return NULL;
    }
    if (!(out_iter_next = NpyIter_GetIterNext(out_iter, NULL))) {
        NpyIter_Deallocate(out_iter);
        return NULL;
    }
    out_array_data_ptr = (unsigned int**)NpyIter_GetDataPtrArray(out_iter);
    out_data_ptr = histb;
    do {
        **(out_array_data_ptr) = *(out_data_ptr++);
    } while (out_iter_next(out_iter));
    NpyIter_Deallocate(out_iter);

    Py_RETURN_NONE;
}


static PyMethodDef _hist_methods[] = {
    {"hist_base", (PyCFunction)hist_base, METH_VARARGS, hist_base__doc__},
    {0}
};

static int _hist_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int _hist_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "imgproc.stats.hist._hist",
    NULL,
    sizeof(struct module_state),
    _hist_methods,
    NULL,
    _hist_traverse,
    _hist_clear,
    NULL
};

PyMODINIT_FUNC PyInit__hist(void) {
    PyObject *module = PyModule_Create(&moduledef);
    if (!module) return NULL;
    import_array();
    return module;
}

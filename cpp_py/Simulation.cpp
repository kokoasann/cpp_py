#include "pch.h"
#include "Simulation.h"


Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vector3::Copy(Vector3 & v)
{
	v.x = x;
	v.y = y;
	v.z = z;
}


static Vector3 p1 = { 0,0,0 };

static PyObject * sp1v(PyObject * self, PyObject * args)
{
	PyObject* tu = PyTuple_New(3);
	PyObject* x = PyLong_FromLong(p1.x);
	PyTuple_SetItem(tu, 0, x);
	PyObject* y = PyLong_FromLong(p1.y);
	PyTuple_SetItem(tu, 1, y);
	PyObject* z = PyLong_FromLong(p1.z);
	PyTuple_SetItem(tu, 2, z);
	return tu;
}
static PyMethodDef methods[] =
{
	{ "p1v", sp1v, METH_VARARGS,	 "Return the number of arguments received by the process." },
	 { NULL,NULL,0,NULL }
};
static PyModuleDef smodule = { PyModuleDef_HEAD_INIT, "Sim", NULL, -1, methods,NULL, NULL, NULL, NULL };
static PyObject * init(void)
{
	return PyModule_Create(&smodule);
}


Simulation::Simulation()
{
	p1.x = 1;
	p1.z = 1;
	p1.y = 1;
}

Simulation::~Simulation()
{
}

void Simulation::pyst()
{
	PyObject *pName, *pModule, *pFunc, *pArgs, *pValue;

	PyImport_AppendInittab("Sim", &init);

	Py_Initialize();
	pName = PyUnicode_DecodeFSDefault("testmodule");
	pModule = PyImport_Import(pName);
	Py_DECREF(pName);
	pFunc = PyObject_GetAttrString(pModule, "tess");
	pArgs = PyTuple_New(0);
	pValue = PyObject_CallObject(pFunc, pArgs);
	Py_DECREF(pModule);
	Py_DECREF(pFunc);
	Py_DECREF(pValue);
}





void Simulation::Setp1(Vector3 v)
{
	v.Copy(p1);
}



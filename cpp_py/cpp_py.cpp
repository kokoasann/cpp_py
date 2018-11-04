// cpp_py.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#include "pch.h"
#include <iostream>


int smain(/*int argc, char *argv[]*/)
{
	int argc = 5;
	char* argv[5];
	char c0[] = "cpp_py";
	char c1[] = "sample";
	char c2[] = "multiply";
	char c3[] = "5";
	char c4[] = "5";
	argv[0] = c0;
	argv[1] = c1;
	argv[2] = c2;
	argv[3] = c3;
	argv[4] = c4;

	PyObject *pName, *pModule, *pDict, *pFunc;
	PyObject *pArgs, *pValue;
	int i;

	if (argc < 3) {
		fprintf(stderr, "Usage: call pythonfile funcname [args]\n");
		return 1;
	}

	Py_Initialize();
	pName = PyUnicode_DecodeFSDefault(argv[1]);
	/* Error checking of pName left out */

	pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	if (pModule != NULL) {
		pFunc = PyObject_GetAttrString(pModule, argv[2]);
		/* pFunc is a new reference */

		if (pFunc && PyCallable_Check(pFunc)) {
			pArgs = PyTuple_New(argc - 3);
			for (i = 0; i < argc - 3; ++i) {
				pValue = PyLong_FromLong(atoi(argv[i + 3]));
				if (!pValue) {
					Py_DECREF(pArgs);
					Py_DECREF(pModule);
					fprintf(stderr, "Cannot convert argument\n");
					return 1;
				}
				/* pValue reference stolen here: */
				PyTuple_SetItem(pArgs, i, pValue);
			}
			pValue = PyObject_CallObject(pFunc, pArgs);
			Py_DECREF(pArgs);
			if (pValue != NULL) {
				printf("Result of call: %ld\n", PyLong_AsLong(pValue));
				Py_DECREF(pValue);
			}
			else {
				Py_DECREF(pFunc);
				Py_DECREF(pModule);
				PyErr_Print();
				fprintf(stderr, "Call failed\n");
				return 1;
			}
		}
		else {
			if (PyErr_Occurred())
				PyErr_Print();
			fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}
	else {
		PyErr_Print();
		fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
		return 1;
	}
	if (Py_FinalizeEx() < 0) {
		return 120;
	}
	return 0;
}

int main()
{
	PyObject *pValue,*pName,*pModu,*pFunc,*pArgs;


	Py_Initialize();

	char c0[] = "testmodule";
	pName = PyUnicode_DecodeFSDefault(c0);

	pModu = PyImport_Import(pName);

	Py_DECREF(pName);

	char c1[] = "function";
	pFunc = PyObject_GetAttrString(pModu, c1);

	long l = 100;
	pValue = PyLong_FromLong(l);

	int i = 1;
	pArgs = PyTuple_New(i);

	PyTuple_SetItem(pArgs, 0, pValue);

	
	pValue = PyObject_CallObject(pFunc, pArgs);
	
	float r = PyFloat_AsDouble(pValue);

	Py_DECREF(pValue);
	
	Py_Finalize();
	printf("%f", r);
	return 0;
}

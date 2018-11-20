#include "pch.h"
#include <iostream>
#include "ThreadTest.h"
#include <Windows.h>

int FindNum(int num)
{
	for (auto tt : tts)
	{
		int mn = tt->Getmynum();
		if (mn == num)
			return mn;
	}
	return 999;
}

PyObject* GetMyNum(PyObject* self, PyObject* args)
{
	PyObject* pi = PyLong_FromLong(FindNum(PyLong_AsLong(PyTuple_GetItem(args,0))));

	return pi;
}

PyObject* printCpp(PyObject* self, PyObject* args)
{
	int cnt = PyTuple_Size(args);
	for (int i = 0; i < cnt; i++)
	{
		PyObject* pitem = PyTuple_GetItem(args, i);
		char* text = PyUnicode_AsUTF8(pitem);
		std::cout << text << "\n";

		delete text;
	}
	return nullptr;
}

PyMethodDef meths[] = {
	{ "GetMyNum",GetMyNum,METH_VARARGS,"aaa" },
	{"printCpp",printCpp,METH_VARARGS,"print"},
	{NULL,NULL,0,NULL}
};
PyModuleDef module = { PyModuleDef_HEAD_INIT, "thretes", NULL, -1, meths,NULL, NULL, NULL, NULL };
PyObject* modinit()
{
	return PyModule_Create(&module);
}
ThreadTest::ThreadTest()
{
}


ThreadTest::~ThreadTest()
{
}


void ThreadTest::Update()
{
	py_exe();

	if (end)
	{
		//PyEval_RestoreThread(ts);
		
		end = false;
		isExe = false;
	}
}

void ThreadTest::py_exe()
{
	if (isExe)
		return;
	isExe = true;

	/*PyEval_InitThreads();

	th.reset(new std::thread([&]
	{
		PyGILState_STATE gils;
		gils = PyGILState_Ensure();*/

		PyObject *pName, *pMod, *pFunc, *pArgs, *pValue;

		char name[] = "thremaster";
		pName = PyUnicode_DecodeFSDefault(name);
		//pName = PyUnicode_DecodeUTF8("thremaster",10,"a");

		pMod = PyImport_Import(pName);
		//pMod = PyImport_ImportModule("thremaster");
		//pMod = PyImport_AddModule("thremaster");

		Py_DECREF(pName);

		pFunc = PyObject_GetAttrString(pMod, "execute");

		pArgs = PyTuple_New(1);
		PyObject* pNum = PyUnicode_DecodeUTF8("threthre",8,"d");
		PyTuple_SetItem(pArgs, 0, pNum);

		PyObject_CallObject(pFunc, pArgs);

		//nextnum = PyLong_AsLong(pValue);
		
		Py_DECREF(pMod);
		Py_DECREF(pFunc);
		//Py_DECREF(pValue);

		end = true;

		/*PyGILState_Release(gils);
	}));
	ts = PyEval_SaveThread();*/
}

pyinit::pyinit()
{
	PyImport_AppendInittab("thretes", modinit);
	//Py_InitializeEx(1);
	Py_Initialize();
}

pyinit::~pyinit()
{
	Py_Finalize();
}

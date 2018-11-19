#include "pch.h"
#include "ThreadTest.h"


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
PyMethodDef meths[] = {
	{ "GetMyNum",GetMyNum,METH_VARARGS,"aaa" },
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

	//PyEval_InitThreads();

	//th.reset(new std::thread([&]
	//{
		//PyGILState_STATE gils;
		//gils = PyGILState_Ensure();

		PyObject *pName, *pMod, *pFunc, *pArgs, *pValue;

		pName = PyUnicode_DecodeFSDefault("threthre");

		pMod = PyImport_Import(pName);

		Py_DECREF(pName);

		pFunc = PyObject_GetAttrString(pMod, "func");

		pArgs = PyTuple_New(1);
		PyObject* pNum = PyLong_FromLong(mynum);
		PyTuple_SetItem(pArgs, 0, pNum);

		pValue = PyObject_CallObject(pFunc, pArgs);

		nextnum = PyLong_AsLong(pValue);
		
		Py_DECREF(pMod);
		Py_DECREF(pFunc);
		Py_DECREF(pValue);

		end = true;

		//PyGILState_Release(gils);
	//}));
	//ts = PyEval_SaveThread();
}

pyinit::pyinit()
{
	PyImport_AppendInittab("thretes", modinit);

	Py_Initialize();
}

pyinit::~pyinit()
{
	Py_Finalize();
}

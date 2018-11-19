#pragma once
#include <thread>

struct pyinit
{
	pyinit();
	~pyinit();
};

class ThreadTest
{
public:
	ThreadTest();
	~ThreadTest();
	//PyObject* PI(PyObject* self, PyObject* args);
	void Update();
	void py_exe();
	std::unique_ptr<std::thread> th;
	PyThreadState* ts;

	bool isExe = false;
	bool end = false;
	int mynum = 0;
	int nextnum = 0;

	int Getmynum()
	{
		return mynum;
	}
	void SetNum(int n)
	{
		mynum = n;
	}
};


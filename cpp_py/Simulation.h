#pragma once
class Vector3
{
public:
	struct
	{
		float x = 0, y = 0, z = 0;
	};
	Vector3(float x,float y,float z);

	void Copy(Vector3 &v);
};

class Simulation
{
public:
	Simulation();
	~Simulation();
	void pyst();
	//static PyObject* p1v(PyObject* self, PyObject* args);
	/*static PyMethodDef methods[2];
	static PyModuleDef module;*/
	void Setp1(Vector3 v);
private:
	//static Vector3 p1;
	Vector3 p2 = { 2,2,2 };
	Vector3 e1 = { 3,3,3 };
	Vector3 e2 = { 4,4,4 };
};


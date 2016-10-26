#ifndef _MODULEFBXLOAD_H_
#define _MODULEFBXLOAD_H_

#include "Module.h"

struct Mesh
{
	uint id_vertices = 0;
	uint num_vertices = 0;
	float* vertices = nullptr;

	uint id_indices = 0;
	uint num_indices = 0;
	int* indices = nullptr;
};

class ModuleFBXLoad : public Module
{
public:
	
	//Constructor
	ModuleFBXLoad();

	//Destructor
	~ModuleFBXLoad();

	//Iterations
	bool Init();
	bool CleanUp();

	//Utils
	void LoadFBX(const char* file) const;



};




#endif _MODULEFBXLOAD_H_

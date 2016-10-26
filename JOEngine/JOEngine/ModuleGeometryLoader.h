#ifndef _MODULEGEOMETRYLOADER_H_
#define _MODULEGEOMETRYLOADER_H_

#include "Module.h"

//WARNING: have to do something about this
#include "DirectX9/Include/d3d9.h"


struct CUSTOMVERTEX;

struct Mesh
{
	uint id_vertices = 0;
	uint num_vertices = 0;
	CUSTOMVERTEX* vertices = nullptr;
	LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;  
	

	uint id_indices = 0;
	uint num_indices = 0;
	uint* indices = nullptr;
	LPDIRECT3DINDEXBUFFER9 i_buffer = NULL;

	uint num_triangles = 0;
};

class ModuleGeometryLoader : public Module
{
public:
	
	//Constructor
	ModuleGeometryLoader(Application* app, bool start_enabled = true);

	//Destructor
	~ModuleGeometryLoader();

	//Iterations
	bool Init();
	bool CleanUp();

	//Utils
	//NOTE: use a pointer/array or a vector?
	//Returns number of meshes loaded
	uint LoadFBX(const char* file) const;



};




#endif _MODULEGEOMETRYLOADER_H_

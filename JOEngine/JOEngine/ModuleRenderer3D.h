#pragma once
#include "Module.h"
#include "Globals.h"
#include "DirectXGlobals.h"
#include "Light.h"
#include <vector>
#define MAX_LIGHTS 8

//WARNING: provisional

struct Mesh;

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	//void OnResize(int width, int height);
	void init_graphics();
	void init_light();
	void LoadMeshes(Mesh* m, uint size);

	void Draw(const Mesh &m);

public:

	//Ask Ric how to put all this here
	/*LPDIRECT3D9 d3d; // the pointer to out Direct3D interface
	LPDIRECT3DDEVICE9 d3ddev; // the pointer to the device class
	LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;    // the pointer to the vertex buffer
	LPDIRECT3DINDEXBUFFER9 i_buffer = NULL;*/
	/*Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	float3x3 NormalMatrix;
	float4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
	*/

	LPDIRECT3D9 d3d = NULL; // the pointer to out Direct3D interface
	D3DPRESENT_PARAMETERS d3dpp; // stores directx parameters
	LPDIRECT3DDEVICE9 d3ddev = NULL; // the pointer to the device class
	/*LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;  // the pointer to the vertex buffer
	LPDIRECT3DINDEXBUFFER9 i_buffer = NULL;  // the pointer to the index buffer*/


	//Provisional
private:
	std::vector<Mesh> meshes;
	uint num_meshes;
};
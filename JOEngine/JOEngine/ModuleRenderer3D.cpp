#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"


#include "DirectX9/Include/d3d9.h"
#include "DirectX9/Include/d3dx9.h"

// include the Direct3D Library files
#pragma comment (lib, "DirectX9/Lib/x64/d3d9.lib")
#pragma comment (lib, "DirectX9/Lib/x64/d3dx9.lib")

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)
struct CUSTOMVERTEX { FLOAT X, Y, Z; D3DVECTOR NORMAL; };

//WARNING: this should go as a member of ModuleRender3D
LPDIRECT3D9 d3d; // the pointer to out Direct3D interface
LPDIRECT3DDEVICE9 d3ddev; // the pointer to the device class
LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;    // the pointer to the vertex buffer
LPDIRECT3DINDEXBUFFER9 i_buffer = NULL;  // the pointer to the index buffer

ModuleRenderer3D::ModuleRenderer3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	LOG("Creating 3D Renderer context");
	bool ret = true;
	
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = App->window->hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		App->window->hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	init_graphics();    // call the function to initialize the triangle
	init_light();

	d3ddev->SetRenderState(D3DRS_LIGHTING, TRUE);    // turn off the 3D lighting
	d3ddev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);    // both sides of the triangles
	d3ddev->SetRenderState(D3DRS_ZENABLE, TRUE);    // turn on the z-buffer
	d3ddev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50)); //sets the ambient light

	/*PRE-DIRECTX
	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if(context == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	
	if(ret == true)
	{
		//Use Vsync
		if(VSYNC && SDL_GL_SetSwapInterval(1) < 0)
			LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
		
		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();
		
		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
	}

	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	App->camera->Look(float3(1.75f, 1.75f, 5.0f), float3(0.0f, 0.0f, 0.0f));*/

	return ret;
}


// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	d3ddev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	/*PRE-DIRECTX
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());

	// light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();
	*/
	return UPDATE_CONTINUE;
}

// Update: debug camera
update_status ModuleRenderer3D::Update(float dt)
{
	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	d3ddev->BeginScene();

	//NOTE: direct primitive drawing
	// select which vertex format we are using
	d3ddev->SetFVF(CUSTOMFVF);

	// SET UP THE PIPELINE
	//transform
	D3DXMATRIX matRotateY;
	D3DXMATRIX matRotateX;


	static float index = 0.0f; index += 0.05f;

	D3DXMatrixRotationY(&matRotateY, index);
	D3DXMatrixRotationX(&matRotateX, index * 2);

	d3ddev->SetTransform(D3DTS_WORLD, &(matRotateY));
	// tell Direct3D about our matrix


	D3DXMATRIX matView;    // the view transform matrix

	D3DXMatrixLookAtLH(&matView,
		&D3DXVECTOR3(0.0f, 0.0f, 10.0f),    // the camera position
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),    // the look-at position
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));    // the up direction

	d3ddev->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView

	D3DXMATRIX matProjection;     // the projection transform matrix

	D3DXMatrixPerspectiveFovLH(&matProjection,
		D3DXToRadian(45),    // the horizontal field of view
		(FLOAT)SCREEN_WIDTH / (FLOAT)SCREEN_HEIGHT, // aspect ratio
		1.0f,    // the near view-plane
		100.0f);    // the far view-plane

	d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);    // set the projection

															   // select the vertex buffer to display
	d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
	d3ddev->SetIndices(i_buffer);


	//d3ddev->SetTransform(D3DTS_WORLD, &(matTranslateA * matRotateY));
	d3ddev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);


	//

	d3ddev->EndScene();

	d3ddev->Present(NULL, NULL, NULL, NULL);
	//PRE-DIRECTX
	//SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOG("Destroying 3D Renderer");

	d3ddev->Release();
	d3d->Release();
	//SDL_GL_DeleteContext(context);

	return true;
}


/*void ModuleRenderer3D::OnResize(int width, int height)
{
	/*glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(ProjectionMatrix.ptr());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}*/

void ModuleRenderer3D::init_graphics()
{
	// create the vertices using the CUSTOMVERTEX struct
	CUSTOMVERTEX vertices[] =
	{
		//Cube
		// Side 1
		{ -2.0f, 2.0f, 2.0f, 0.0f,0.0f, 1.0f }, //0
		{ 2.0f, 2.0f, 2.0f, 0.0f, 0.0f, 1.0f }, //1
		{ -2.0f,-2.0f, 2.0f, 0.0f, 0.0f, 1.0f },//2
		{ 2.0f, -2.0f, 2.0f, 0.0f, 0.0f, 1.0f },//3

												// Side 2
		{ -2.0f, 2.0f, -2.0f, -1.0f, 0.0f, 0.0f },//4
		{ -2.0f, 2.0f, 2.0f, -1.0f, 0.0f, 0.0f },//5
		{ -2.0f, -2.0f, -2.0f, -1.0f, 0.0f, 0.0f },//6
		{ -2.0f, -2.0f, 2.0f, -1.0f, 0.0f, 0.0f },//7

												  // Side 3
		{ -2.0f, -2.0f, 2.0f, 0.0f, -1.0f, 0.0f },//8
		{ 2.0f, -2.0f, 2.0f, 0.0f, -1.0f, 0.0f },//9
		{ -2.0f, -2.0f, -2.0f, 0.0f, -1.0f, 0.0f },//10
		{ 2.0f, -2.0f, -2.0f, 0.0f, -1.0f, 0.0f },//11

												  //Side 4
		{ 2.0f, 2.0f, -2.0f, 0.0f, 0.0f, -1.0f },//12
		{ -2.0f, 2.0f, -2.0f, 0.0f, 0.0f, -1.0f },//13
		{ 2.0f, -2.0f, -2.0f, 0.0f, 0.0f - 1.0f },//14
		{ -2.0f, -2.0f, -2.0f, 0.0f, 0.0f, -1.0f },//15
												   //Side 5
		{ 2.0f, 2.0f, 2.0f, 1.0f, 0.0f, 0.0f },//16
		{ 2.0f, 2.0f, -2.0f, 1.0f, 0.0f, 0.0f },//17
		{ 2.0f, -2.0f, 2.0f, 1.0f, 0.0f, 0.0f },//18
		{ 2.0f, -2.0f, -2.0f, 1.0f, 0.0f, 0.0f },//19

												 //Side 6
		{ -2.0f, 2.0f, -2.0f, 0.0f, 1.0f, 0.0f },//20
		{ 2.0f, 2.0f, -2.0f, 0.0f, 1.0f, 0.0f },//21
		{ -2.0f, 2.0f, 2.0f, 0.0f, 1.0f, 0.0f },//22
		{ 2.0f, 2.0f, 2.0f, 0.0f, 1.0f, 0.0f },//23






											   //Pyramid
											   /*{0.0f, 2.0f, 0.0f, D3DCOLOR_XRGB(0,0,255),}, //0
											   {-2.0f, -2.0f, -2.0f, D3DCOLOR_XRGB(0,255,0),}, //1
											   {2.0f, -2.0f, -2.0f, D3DCOLOR_XRGB(255,0,0),}, //2
											   {-2.0f, -2.0f, 2.0f, D3DCOLOR_XRGB(0,255,255),}, //3
											   {2.0f, -2.0f, 2.0f, D3DCOLOR_XRGB(255,255,0),}, //4*/
	};

	// create a vertex buffer interface called v_buffer
	d3ddev->CreateVertexBuffer(24 * sizeof(CUSTOMVERTEX),
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&v_buffer,
		NULL);

	VOID* pVoid;    // a void pointer

					// lock v_buffer and load the vertices into it
	v_buffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, vertices, sizeof(vertices));
	v_buffer->Unlock();

	//indexes
	short indices[]
	{
		//Cube
		0,1,3,
		0,2,3,

		4,5,7,
		4,6,7,

		8,9,11,
		8,10,11,

		12,14,15,
		12,13,15,

		16,18,19,
		16,17,19,

		20,22,23,
		20,21,23,

	};

	d3ddev->CreateIndexBuffer(
		36 * sizeof(short),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&i_buffer,
		NULL);

	// lock i_buffer and load the indices into it
	i_buffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, indices, sizeof(indices));
	i_buffer->Unlock();
}


void ModuleRenderer3D::init_light()
{
	D3DLIGHT9 light;    // create the light struct
	D3DMATERIAL9 material; //create the material struct

	ZeroMemory(&light, sizeof(light));    // clear out the light struct for use
	light.Type = D3DLIGHT_DIRECTIONAL;    // make the light type 'directional light'
	light.Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);    // set the light's color
	light.Direction = D3DXVECTOR3(-1.0f, -0.3f, -1.0f);

	d3ddev->SetLight(0, &light);    // send the light struct properties to light #0
	d3ddev->LightEnable(0, TRUE);    // turn on light #0

	ZeroMemory(&material, sizeof(D3DMATERIAL9));    // clear out the struct for use
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set diffuse color to white
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);    // set ambient color to white

	d3ddev->SetMaterial(&material);    // set the globably-used material to &material
}

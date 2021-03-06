#include "Application.h"

//IMGUI 
#include "Imgui\imgui.h"
#include "Imgui\imgui_impl_dx9.h"


Application::Application()
{
	frames = 0;
	last_frame_ms = -1;
	last_fps = -1;
	capped_ms = 1000 / 60;
	fps_counter = 0;

	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this, true);
	scene_intro = new ModuleSceneIntro(this);
	//physics3D = new ModulePhysics3D(this);
	renderer3D = new ModuleRenderer3D(this);
	geoload = new ModuleGeometryLoader(this);
	camera = new ModuleCamera3D(this);
	editor = new ModuleEditor(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	//AddModule(physics3D);
	AddModule(renderer3D);
	//WARNING : provisional module
	AddModule(geoload);
	AddModule(camera);
	AddModule(input);
	AddModule(audio);
	
	// Scenes
	AddModule(scene_intro);
	
	// Characters

	//Editor
	AddModule(editor);
}

Application::~Application()
{
	p2List_item<Module*>* item = list_modules.getLast();

	while(item != NULL)
	{
		delete item->data;
		item = item->prev;
	}
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	p2List_item<Module*>* item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		ret = item->data->Init();
		item = item->next;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		if(item->data->IsEnabled())
			ret = item->data->Start();
		item = item->next;
	}
	
	return ret;
}


// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	// Recap on framecount and fps
	++frames;
	++fps_counter;

	if(fps_timer.Read() >= 1000)
	{
		last_fps = fps_counter;
		fps_counter = 0;
		fps_timer.Start();
	}

	last_frame_ms = ms_timer.Read();

	// cap fps
	if(last_frame_ms < capped_ms)
	{
		SDL_Delay(capped_ms - last_frame_ms);
	}

	//char t[50];
	//sprintf_s(t, "FPS: %d", (int)last_fps);
	//window->SetTitle(t);
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	p2List_item<Module*>* item = list_modules.getFirst();
	
	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->PreUpdate(dt);
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
  			ret = item->data->Update(dt);
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->PostUpdate(dt);
		item = item->next;
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	p2List_item<Module*>* item = list_modules.getLast();

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.add(mod);
}

void Application::RequestBrowser(const char * url) const
{
	ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}


//WINDOWPROC
extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Application::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	//App->editor
	if (ImGui_ImplDX9_WndProcHandler(hWnd, message, wParam, lParam))
		return true;

	switch (message)
	{
		
		case WM_SIZE:
		if (App->renderer3D->d3ddev != NULL && wParam != SIZE_MINIMIZED)
		{
			/*App->renderer3D->d3ddev->BeginScene();
			ImGui_ImplDX9_InvalidateDeviceObjects();
			App->renderer3D->d3dpp.BackBufferWidth = LOWORD(lParam);
			App->renderer3D->d3dpp.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = App->renderer3D->d3ddev->Reset(&(App->renderer3D->d3dpp));
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);

			ImGui_ImplDX9_CreateDeviceObjects();*/
		}
		return 0;

		case WM_SYSCOMMAND:
			if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_INPUT:
		{
			/*RAWINPUT InputData;

			UINT DataSize = sizeof(RAWINPUT);
			GetRawInputData((HRAWINPUT)lParam,
				RID_INPUT,
				&InputData,
				&DataSize,
				sizeof(RAWINPUTHEADER));

			// set the mouse button status
			static BOOL MouseDown;
			if (InputData.data.mouse.usButtonFlags == RI_MOUSE_LEFT_BUTTON_DOWN)
				MouseDown = TRUE;
		break;*/
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
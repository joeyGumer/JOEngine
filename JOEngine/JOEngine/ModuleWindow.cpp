#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"


//IMGUI NOTE: Should I do this?
#include "Imgui\imgui.h"
#include "Imgui\imgui_impl_dx9.h"

ModuleWindow::ModuleWindow(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// NOTE: declaring WindowProc here due to some errors in previous initialization
extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplDX9_WndProcHandler(hWnd, message, wParam, lParam))
		return true;

	switch (message)
	{
	/*case WM_SIZE:
		if (App->render->d3ddev != NULL && wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX9_InvalidateDeviceObjects();
			g_d3dpp.BackBufferWidth = LOWORD(lParam);
			g_d3dpp.BackBufferHeight = HIWORD(lParam);
			HRESULT hr = g_pd3dDevice->Reset(&g_d3dpp);
			if (hr == D3DERR_INVALIDCALL)
				IM_ASSERT(0);
			ImGui_ImplDX9_CreateDeviceObjects();
		}
		return 0;*/
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init DirectX9 Window");
	bool ret = true;

	/*if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}*/
	
		//Create window
		int width = SCREEN_WIDTH * SCREEN_SIZE;
		int height = SCREEN_HEIGHT * SCREEN_SIZE;
		
		// clear out the window class for use
		ZeroMemory(&wc, sizeof(WNDCLASSEX));

		// fill in the struct with the needed information
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = GetModuleHandle(0);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.lpszClassName = "WindowClass1";

		// register the window class
		RegisterClassEx(&wc);

		HINSTANCE hInstatnce = GetModuleHandle(0);
		// create the window and use the result as the handle
		int i = 0;
		hWnd = CreateWindowEx(NULL,
			"WindowClass1",    // name of the window class
			TITLE,   // title of the window
			WS_OVERLAPPEDWINDOW,    // window style
			100,    // x-position of the window
			100,    // y-position of the window
			width,    // width of the window
			height,    // height of the window
			NULL,    // we have no parent window, NULL
			NULL,    // we aren't using menus, NULL
			hInstatnce,    // application handle
			NULL);    // used with multiple windows, NULL
			

		// display the window on the screen
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		

		//PRE-DIRECTX CODE
		/*if(WIN_FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if(WIN_RESIZABLE == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		if(WIN_BORDERLESS == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if(WIN_FULLSCREEN_DESKTOP == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}*/

	return ret;
}


// Called before quitting
bool ModuleWindow::CleanUp()
{
	/*LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}*/

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

update_status ModuleWindow::PreUpdate(float dt)
{
	//Handling window events
	/*MSG msg;

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (msg.message == WM_QUIT)
		return UPDATE_STOP;*/

	return UPDATE_CONTINUE;
}

void ModuleWindow::SetTitle(const char* title)
{
	//SDL_SetWindowTitle(window, title);
	
}


#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"

#include <windowsx.h>
#include <dinput.h>

#define MAX_KEYS 300

ModuleInput::ModuleInput(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	keyboard = new KEY_STATE[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);

	//Filed by hand due to incapacity to fill an array with mouse flags
	/*mouse_buttons[MOUSE_LEFT_BUTTON] = { KEY_IDLE , RI_MOUSE_LEFT_BUTTON_DOWN };
	mouse_buttons[MOUSE_RIGHT_BUTTON] = { KEY_IDLE , RI_MOUSE_RIGHT_BUTTON_DOWN };
	mouse_buttons[MOUSE_MIDDLE_BUTTON] = { KEY_IDLE , RI_MOUSE_MIDDLE_BUTTON_DOWN };*/

}

// Destructor
ModuleInput::~ModuleInput()
{
	delete[] keyboard;
}

// Called before render is available
bool ModuleInput::Init()
{
	//NOTE: this will need to be out
	LOG("Init Direct input event system");
	bool ret = true;
	/*SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}*/
	

	mouse.usUsage = 0x02;    // register mouse
	mouse.usUsagePage = 0x01;    // top-level mouse
	mouse.dwFlags = NULL;    // flags
	mouse.hwndTarget = App->window->hWnd;    // handle to a window

	RegisterRawInputDevices(&mouse, 1, sizeof(RAWINPUTDEVICE));

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate(float dt)
{
	/*SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);*/

	
	
	for(int i = 0x00; i < MAX_KEYS; ++i)
	{
		if(GetAsyncKeyState(i))
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
		else
				keyboard[i] = KEY_IDLE;
		}
	}

	//Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

	mouse_x /= SCREEN_SIZE;
	mouse_y /= SCREEN_SIZE;
	mouse_z = 0;

	/*for(int i = 0; i < 5; ++i)
	{
		if(true)
		{
			if(mouse_buttons[i].state == KEY_IDLE)
				mouse_buttons[i].state = KEY_DOWN;
			else
				mouse_buttons[i].state = KEY_REPEAT;
		}
		else
		{
			if(mouse_buttons[i].state == KEY_REPEAT || mouse_buttons[i].state == KEY_DOWN)
				mouse_buttons[i].state = KEY_UP;
			else
				mouse_buttons[i].state = KEY_IDLE;
		}
	}*/

	mouse_x_motion = mouse_y_motion = 0;

	bool quit = false;
	/*SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
			case SDL_MOUSEWHEEL:
			mouse_z = e.wheel.y;
			break;

			case SDL_MOUSEMOTION:
			mouse_x = e.motion.x / SCREEN_SIZE;
			mouse_y = e.motion.y / SCREEN_SIZE;

			mouse_x_motion = e.motion.xrel / SCREEN_SIZE;
			mouse_y_motion = e.motion.yrel / SCREEN_SIZE;
			break;

			case SDL_QUIT:
			quit = true;
			break;

			//WARNING: change
			case SDL_WINDOWEVENT:
			{
				//if(e.window.event == SDL_WINDOWEVENT_RESIZED)
					//App->renderer3D->OnResize(e.window.data1, e.window.data2);
			}
		}
	}*/
	//Windows input handler
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	switch (msg.message)
	{
		case WM_MOUSEWHEEL:
		{
			mouse_z = GET_WHEEL_DELTA_WPARAM(msg.wParam);
			break;
		}
		case WM_MOUSEMOVE:
		{
			int tmp_x = mouse_x;
			int tmp_y = mouse_y;

			mouse_x = GET_X_LPARAM(msg.lParam);
			mouse_y = GET_Y_LPARAM(msg.lParam);

			mouse_x_motion = mouse_x - tmp_x;
			mouse_y_motion = mouse_y - tmp_y;
			break;
		}
		case WM_QUIT:
		{
			return UPDATE_STOP;
			break;
		}
	}

	//

	if(quit == true || keyboard[SDL_SCANCODE_ESCAPE] == KEY_UP)
		return UPDATE_STOP;

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}


bool ModuleInput::ReadMouseInput()
{
	return true;
}
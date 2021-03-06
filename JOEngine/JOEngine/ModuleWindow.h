#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	update_status PreUpdate(float dt);
	bool CleanUp();

	void SetTitle(const char* title);
	

private:

	//NOTE: Ask ric how to handle this
	//LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	

public:

	// the window handler
	HWND hWnd;
	// this struct holds information for the window class
	WNDCLASSEX wc;
};

#endif // __ModuleWindow_H__
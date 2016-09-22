#pragma once

#ifndef _MODULEEDITOR_H_
#define _MODULEEDITOR_H_

#include "Module.h"
#include "Globals.h"

class Application;

class ModuleEditor : public Module
{
public:

	ModuleEditor(Application* parent, bool start_enabled = true);
	~ModuleEditor();

	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

private:

};




#endif // !_MODULEEDITOR_H_

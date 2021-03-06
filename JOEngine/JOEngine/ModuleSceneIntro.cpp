#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "InputDefs.h"
//#include "ModuleInput.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	//App->camera->Move(float3(0, 10, -10));
	
	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	
	return true;
}

update_status ModuleSceneIntro::PreUpdate(float dt)
{
	
	

	return UPDATE_CONTINUE;
}
// Update: draw background
update_status ModuleSceneIntro::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;



	/*if (App->input->GetKey(VK_LBUTTON))
	{
		int i = 0;
	}*/
	




	return ret;
}

update_status ModuleSceneIntro::PostUpdate(float dt)
{

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{

}

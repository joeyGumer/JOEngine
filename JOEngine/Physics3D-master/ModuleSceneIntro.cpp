#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"


//ImGui provisional

#include <cstdlib>
#include "ImGui/GL/gl3w.h"
#include "ImGui/imgui_impl_sdl_gl3.h"
#include "ImGui/imgui.h"


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

	App->camera->Move(vec3(0, 30, -30));


	//ImGui test
	gl3wInit();
	ImGui_ImplSdlGL3_Init(App->window->window);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update(float dt)
{
	Plane(0, 1, 0, 0).Render();

	//Simple window? ImGui
	static bool show_window = true;
	
	ImGui_ImplSdlGL3_NewFrame(App->window->window);

	ImGui::ShowTestWindow(&show_window);

	ImGui::Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	int a = 0;
}

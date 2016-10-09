#include "ModuleEditor.h"
#include "Application.h"


//IMGUI 
/*#include "Imgui\imgui.h"
#include "Imgui\imgui_impl_sdl_gl3.h"
#include "Imgui\GL\gl3w.h"


//Constructor
ModuleEditor::ModuleEditor(Application* parent, bool start_enabled) : Module(parent,start_enabled)
{

}

//Destructor
ModuleEditor::~ModuleEditor()
{

}

//Start
bool ModuleEditor::Start()
{
	gl3wInit();

	ImGui_ImplSdlGL3_Init(App->window->window);

	return true;
}

//CleanUp
bool ModuleEditor::CleanUp()
{
	ImGui_ImplSdlGL3_Shutdown();

	return true;
}

//Preupdate
update_status ModuleEditor::PreUpdate(float dt)
{
	ImGui_ImplSdlGL3_NewFrame(App->window->window);
	return UPDATE_CONTINUE;
}

//Update
update_status ModuleEditor::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	static bool show_test_window = true;

	//Test Window to know how ImGui buttons works
	ImGui::ShowTestWindow(&show_test_window);

	//Main menu
	if (ImGui::BeginMainMenuBar())
	{
		//Quit Button
		if (ImGui::MenuItem("Quit"))
		{
			ret = UPDATE_STOP;
		}

		ImGui::EndMainMenuBar();
	}

	//Renders what is suposed to
	ImGui::Render();


	return ret;
}

//PostUpdate
update_status ModuleEditor::PostUpdate(float dt)
{

	return UPDATE_CONTINUE;
}
*/



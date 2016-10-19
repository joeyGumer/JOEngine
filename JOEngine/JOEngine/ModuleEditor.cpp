#include "ModuleEditor.h"
#include "Application.h"


//IMGUI 
#include "Imgui\imgui.h"
#include "Imgui\imgui_impl_dx9.h"


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
	ImGui_ImplDX9_Init(App->window->hWnd, App->renderer3D->d3ddev);

	return true;
}

//CleanUp
bool ModuleEditor::CleanUp()
{
	ImGui_ImplDX9_Shutdown();

	return true;
}

//Preupdate
update_status ModuleEditor::PreUpdate(float dt)
{
	ImGui_ImplDX9_NewFrame();

	update_status ret = UPDATE_CONTINUE;

	
	return ret;

}

//Update
update_status ModuleEditor::Update(float dt)
{

	update_status ret = UPDATE_CONTINUE;


	return ret;
}

//PostUpdate
update_status ModuleEditor::PostUpdate(float dt)
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

	if (App->renderer3D->d3ddev->BeginScene() >= 0)
	{
	ImGui::Render();
	App->renderer3D->d3ddev->EndScene();
	}
	
	App->renderer3D->d3ddev->Present(NULL, NULL, NULL, NULL);

	return ret;
}


void ModuleEditor::RenderEditor()
{
	

	//ImGui::Render();
}

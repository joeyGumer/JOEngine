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

	static bool show_test_window = false;

	//Test Window to know how ImGui buttons works
	if(show_test_window)
		ImGui::ShowTestWindow(&show_test_window);

	//Main menu----------------------------
	if (ImGui::BeginMainMenuBar())
	{
		//File
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
				ret = UPDATE_STOP;

			ImGui::EndMenu();
		}

		//Help Button
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Gui Demo"))
				show_test_window = !show_test_window;

			if (ImGui::MenuItem("Documentation"))
				App->RequestBrowser("https://github.com/joeyGumer/JOEngine/wiki");

			if (ImGui::MenuItem("Download last"))
				App->RequestBrowser("https://github.com/joeyGumer/JOEngine/releases");

			if (ImGui::MenuItem("Report a bug"))
				App->RequestBrowser("https://github.com/joeyGumer/JOEngine/issues");

			//if(ImGui::)
			
			ImGui::EndMenu();
		}

		//Motor Configuration
		if (ImGui::BeginMenu("Configuration"))
		{
			
			ImGui::EndMenu();
		}

		//About
		if (ImGui::BeginMenu("About"))
		{

			ImGui::EndMenu();
		}


		ImGui::EndMainMenuBar();
	}

	//NOTE: do it here?
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

#include "Globals.h"
#include "Application.h"
#include "PhysBody3D.h"
#include "ModuleCamera3D.h"

ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	CalculateViewMatrix();

	X = float3(1.0f, 0.0f, 0.0f);
	Y = float3(0.0f, 1.0f, 0.0f);
	Z = float3(0.0f, 0.0f, 1.0f);

	Position = float3(0.0f, 0.0f, 10.0f);
	Reference = float3(0.0f, 0.0f, 0.0f);

	following = NULL;
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
	// Follow code
	// NOTE: may be useful in the future
	/*if(following != NULL)
	{
		float4x4 m;
		following->GetTransform(m.ptr());

		Look(Position, m.TranslatePart(), true);

		// Correct height
		Position.y = (15.0*Position.y + Position.y + following_height) / 16.0;

		// Correct distance
		float3 cam_to_target = m.TranslatePart() - Position;
		float dist = cam_to_target.Length();
		float correctionFactor = 0.f;
		if(dist < min_following_dist)
		{
			correctionFactor = 0.15*(min_following_dist - dist) / dist;
		}
		if(dist > max_following_dist)
		{
			correctionFactor = 0.15*(max_following_dist - dist) / dist;
		}
		Position -= correctionFactor * cam_to_target;
	}*/

	// Implement a debug camera with keys and mouse

	// OnKeys WASD keys -----------------------------------
	/*float Speed = 5.0f;

	if(App->input->GetKey(VK_LSHIFT) == KEY_REPEAT) Speed *= 2.0f;
	if(App->input->GetKey(VK_LMENU) == KEY_REPEAT) Speed *= 0.5f;

	float Distance = Speed * dt;

	float3 Up(0.0f, 1.0f, 0.0f);
	float3 Right = X;
	float3 Forward = Cross(Up, Right);

	Up *= Distance;
	Right *= Distance;
	Forward *= Distance;

	float3 Movement;

	if(App->input->GetKey(VK_W) == KEY_REPEAT) Movement += Forward;
	if(App->input->GetKey(VK_S) == KEY_REPEAT) Movement -= Forward;
	if(App->input->GetKey(VK_A) == KEY_REPEAT) Movement -= Right;
	if(App->input->GetKey(VK_D) == KEY_REPEAT) Movement += Right;
	if(App->input->GetKey(VK_R) == KEY_REPEAT) Movement += Up;
	if(App->input->GetKey(VK_F) == KEY_REPEAT) Movement -= Up;

	Position += Movement;
	Reference += Movement;
	
	// Mouse motion ----------------

	if(App->input->GetKey(VK_RBUTTON) == KEY_REPEAT)
	{

		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();

		float Sensitivity = 0.25f;

		Position -= Reference;

		if(dx != 0)
		{
			float DeltaX = (float)dx * Sensitivity;
			
			Quat q = { float3(0.0f, 1.0f, 0.0f), DeltaX };

			q.Transform(X);
			q.Transform(Y);
			q.Transform(Z);
	
			//Code before MathGeoLib
			/*X = rotate(X, DeltaX, float3(0.0f, 1.0f, 0.0f));
			Y = rotate(Y, DeltaX, float3(0.0f, 1.0f, 0.0f));
			Z = rotate(Z, DeltaX, float3(0.0f, 1.0f, 0.0f));*/
		/*}

		if(dy != 0)
		{
			float DeltaY = (float)dy * Sensitivity;

			Quat q = { X, DeltaY };

			q.Transform(Y);
			q.Transform(Z);

			if(Y.y < 0.0f)
			{
				Z = float3(0.0f, Z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
				Y = Cross(Z, X);
			}
		}

		Position = Reference + Z * Position.Length();
	}

	// Mouse wheel -----------------------

	float zDelta = (float) App->input->GetMouseZ();

	Position -= Reference;

	if(zDelta < 0 && Position.Length() < 500.0f)
	{
		Position += Position * 0.1f;
	}

	if(zDelta > 0 && Position.Length() > 0.05f)
	{
		Position -= Position * 0.1f;
	}

	Position += Reference;*/

	// Recalculate matrix -------------
	CalculateViewMatrix();

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const float3 &Position, const float3 &Reference, bool RotateAroundReference)
{
	this->Position = Position;
	this->Reference = Reference;

	Z = (Position-Reference).Normalized();
	X = (Cross(float3(0.0f, 1.0f, 0.0f), Z)).Normalized();
	Y = Cross(Z, X);

	if(!RotateAroundReference)
	{
		this->Reference = this->Position;
		this->Position += Z * 0.05f;
	}

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
void ModuleCamera3D::Move(const float3 &Movement)
{
	Position += Movement;
	Reference += Movement;

	CalculateViewMatrix();
}

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return ViewMatrix.ptr();
}

// -----------------------------------------------------------------
void ModuleCamera3D::CalculateViewMatrix()
{
	ViewMatrix = float4x4(X.x, Y.x, Z.x, 0.0f, X.y, Y.y, Z.y, 0.0f, X.z, Y.z, Z.z, 0.0f, -Dot(X, Position), -Dot(Y, Position), -Dot(Z, Position), 1.0f);
	ViewMatrixInverse = ViewMatrix.Inverted();
}

// -----------------------------------------------------------------
void ModuleCamera3D::Follow(PhysBody3D* body, float min, float max, float height)
{
	min_following_dist = min;
	max_following_dist = max;
	following_height = height;
	following = body;
}

// -----------------------------------------------------------------
void ModuleCamera3D::UnFollow()
{
	following = NULL;
}

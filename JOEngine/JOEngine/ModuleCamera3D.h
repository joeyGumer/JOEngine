#pragma once
#include "Module.h"
#include "Globals.h"
#include "Math.h"

class ModuleCamera3D : public Module
{
	/*
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Follow(PhysBody3D* body, float min, float max, float height);
	void UnFollow();
	void Look(const float3 &Position, const float3 &Reference, bool RotateAroundReference = false);
	void Move(const float3 &Movement);
	float* GetViewMatrix();

private:

	void CalculateViewMatrix();

public:
	
	float3 X, Y, Z, Position, Reference;

private:

	float4x4 ViewMatrix, ViewMatrixInverse;
	PhysBody3D* following;
	float min_following_dist;
	float max_following_dist;
	float following_height;
	*/
};
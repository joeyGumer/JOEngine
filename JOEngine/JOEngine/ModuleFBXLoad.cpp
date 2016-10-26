#include "ModuleFBXLoad.h"
#include "Application.h"
#include "Globals.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

//Constructor
ModuleFBXLoad::ModuleFBXLoad() : Module(App)
{

}

//Destructor
ModuleFBXLoad::~ModuleFBXLoad()
{

}

//Iterations
bool ModuleFBXLoad::Init()
{
	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return true;
}

bool ModuleFBXLoad::CleanUp()
{
	// detach log stream
	aiDetachAllLogStreams();

	return true;
}

//Utils
void ModuleFBXLoad::LoadFBX(const char* full_path)const
{
	const aiScene* scene = aiImportFile(full_path, aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		aiReleaseImport(scene);
	}
	else
	{
		//LOG(“Error loading scene %s”, full_path);
	}
}
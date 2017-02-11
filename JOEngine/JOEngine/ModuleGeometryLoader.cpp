#include "ModuleGeometryLoader.h"
#include "Application.h"
#include "Globals.h"
#include "DirectXGlobals.h"
#include "ModuleRenderer3D.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

//Constructor
ModuleGeometryLoader::ModuleGeometryLoader(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

//Destructor
ModuleGeometryLoader::~ModuleGeometryLoader()
{

}

//Iterations
bool ModuleGeometryLoader::Init()
{
	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);
	
	return true;
}

bool ModuleGeometryLoader::CleanUp()
{
	// detach log stream
	aiDetachAllLogStreams();
	
	return true;
}

//Utils
uint ModuleGeometryLoader::LoadFBX(const char* full_path)const
{
	
	const aiScene* scene = aiImportFile(full_path, aiProcessPreset_TargetRealtime_MaxQuality);
	uint ret_meshes = 0;

	if (scene != nullptr && scene->HasMeshes())
	{
		
		aiMesh** mesh_array = scene->mMeshes;
		
		ret_meshes = scene->mNumMeshes;
		Mesh* ret = new Mesh[ret_meshes];

		//Store all meshes
		for (uint i = 0; i < ret_meshes; i++)
		{
			aiMesh* new_mesh = mesh_array[i];
			Mesh m;
			
			//VERTICES (with normals)
			m.num_vertices = new_mesh->mNumVertices;
			m.vertices = new CUSTOMVERTEX[m.num_vertices];

			for (int i = 0; i < m.num_vertices; i++)
			{
				CUSTOMVERTEX vertex;

				vertex.X =	new_mesh->mVertices[i].x;
				vertex.Y = new_mesh->mVertices[i].y;
				vertex.Z = new_mesh->mVertices[i].z;

				if (!new_mesh->HasNormals())
				{
					LOG("WARNING, vertex and mesh with no normals");
				}
				else
				{
					vertex.NORMAL = { new_mesh->mNormals[i].x, new_mesh->mNormals[i].y, new_mesh->mNormals[i].z };
					m.num_normals++;
				}

				m.vertices[i] = vertex;


			}

			//Creating the vertex buffer
			App->renderer3D->d3ddev->CreateVertexBuffer(m.num_vertices * sizeof(CUSTOMVERTEX),
														0,
														CUSTOMFVF,
														D3DPOOL_MANAGED,
														&(m.v_buffer),
														NULL);

			VOID* pVoid; 
			// lock v_buffer and load the vertices into it
			m.v_buffer->Lock(0, 0, (void**)&pVoid, 0);
			memcpy(pVoid, m.vertices, sizeof(m.vertices));
			m.v_buffer->Unlock();

			// INDICES
			if (new_mesh->HasFaces())
			{
				m.num_triangles = new_mesh->mNumFaces;
				m.num_indices = new_mesh->mNumFaces * 3;
				m.indices = new short[m.num_indices]; // assume each face is a triangle
				for (uint i = 0; i < new_mesh->mNumFaces; ++i)
				{
					if (new_mesh->mFaces[i].mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");
					}
					else
						memcpy(&m.indices[i * 3], new_mesh->mFaces[i].mIndices, 3 * sizeof(short));

				}

				//Creating the index buffer
				App->renderer3D->d3ddev->CreateIndexBuffer(
					m.num_indices * sizeof(short),
					0,
					D3DFMT_INDEX16,
					D3DPOOL_MANAGED,
					&(m.i_buffer),
					NULL);

				// lock i_buffer and load the indices into it
				m.i_buffer->Lock(0, 0, (void**)&pVoid, 0);
				memcpy(pVoid, m.indices, sizeof(m.indices));
				m.i_buffer->Unlock();

				ret[i] = m;

			}
		}

		App->renderer3D->LoadMeshes(ret, ret_meshes);

		aiReleaseImport(scene);
	}
	else
	{
		LOG("Error loading scene %s", full_path);
	}

	return ret_meshes;
}
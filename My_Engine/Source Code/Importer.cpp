#include "Globals.h"
#include "Importer.h"
#include "Assimp.h"
#include "Application.h"

#pragma comment (lib, "assimp.lib")

#include <cmath>

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

bool Mesh::LoadMesh(const std::string& Filename)
{
	Clear();
	
	bool ret = false;
	//import the scene from a file
	const char* file_path = Filename.c_str(); //I use c_str here to prevent accessing weird places if Filename gets deleted or something before getting to this point.
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	
	/*Assimp::Importer Importer; //what is this? Could it be a better implementation?
	const aiScene* pScene = Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);*/

	//Make sure the scene was loaded correctly
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			// New mesh
			MeshEntry ourMesh;
			aiMesh* currentMesh = scene->mMeshes[i];
			// copy vertices
			ourMesh.num_vertex = currentMesh->mNumVertices;
			// create a float array with 3 times the size of the number of vertices of the mesh
			ourMesh.vertex = new float[ourMesh.num_vertex * 3];
			// store into the previously created array the content of the vertices array of the mesh we are loading
			memcpy(ourMesh.vertex, currentMesh->mVertices, sizeof(float) * ourMesh.num_vertex * 3);
			LOG("New mesh added with %d vertices", ourMesh.num_vertex);

			//copy faces
			if (currentMesh->HasFaces())
			{
				//copy number of indices
				ourMesh.num_index = currentMesh->mNumFaces * 3;
				//create an array with the size of the number of indices
				ourMesh.index = new uint[ourMesh.num_index];
				//for each face
				for (uint i = 0; i < currentMesh->mNumFaces; ++i)
				{
					if (currentMesh->mFaces->mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");	
					}
					else
					{
						memcpy(&ourMesh.index[i * 3], currentMesh->mFaces[i].mIndices, 3 * sizeof(uint));
					}
						//copy the 3 face indices into our indices array
				}
			}

		}

		aiReleaseImport(scene);
	}
	else
		LOG("Error loading scene %s", file_path);

	return ret;
}

void Mesh::Render()
{
	//render no va aqui
	//mirar que hace falta exctamente que ha de retornar el importer para que render pueda pintar las meshes.
}

bool Mesh::InitFromScene(const aiScene* pScene, const std::string& Filename)
{
	return false;
}

void Mesh::InitMesh(unsigned int Index, const aiMesh* paiMesh)
{
}

bool Mesh::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
	return false;
}
 
void Mesh::Clear()
{
}

//MeshEntry

Mesh::MeshEntry::MeshEntry()
{

}

Mesh::MeshEntry::~MeshEntry()
{

}

bool Mesh::MeshEntry::Init(const std::vector<int>& Vertices,
	const std::vector<int>& Indices)
{
	return true;
}
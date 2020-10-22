#include "Globals.h"
#include "Importer.h"
#include "Assimp.h"
#include "Application.h"

#pragma comment (lib, "assimp.lib")

#include <cmath>

Importer::Importer()
{

}

Importer::~Importer()
{
}

bool Importer::LoadScene(const std::string& filename, std::vector<uint> mesh_array) 
{	
	bool ret = false;
	//import the scene from a file
	const char* file_path = filename.c_str(); //I use c_str here to prevent accessing weird places if Filename gets deleted or something before getting to this point.
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	
	/*Assimp::Importer Importer; //what is this? Could it be a better implementation?
	const aiScene* pScene = Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);*/
	
	//Make sure the scene was loaded correctly
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			MeshEntry* ourMesh = new MeshEntry;
			// New mesh
			aiMesh* currentMesh = scene->mMeshes[i];
			// copy vertices
			ourMesh->num_vertex = currentMesh->mNumVertices;
			// create a float array with 3 times the size of the number of vertices of the mesh
			ourMesh->vertex = (float*)alloca((ourMesh->num_vertex * 3) * sizeof(float));
			// store into the previously created array the content of the vertices array of the mesh we are loading
			memcpy(ourMesh->vertex, currentMesh->mVertices, sizeof(float) * ourMesh->num_vertex * 3);
			LOG("New mesh added with %d vertices", ourMesh->num_vertex);

			//copy faces
			if (currentMesh->HasFaces())
			{
				//copy number of indices
				ourMesh->num_index = currentMesh->mNumFaces * 3;
				//create an array with the size of the number of indices
				ourMesh->index = (uint*)alloca((ourMesh->num_index) * sizeof(uint));
				//for each face
				for (uint i = 0; i < currentMesh->mNumFaces; ++i)
				{
					if (currentMesh->mFaces->mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");	
					}
					else
					{
						memcpy(&ourMesh->index[i * 3], currentMesh->mFaces[i].mIndices, 3 * sizeof(uint));
					}
						//copy the 3 face indices into our indices array
				}

				m_Entries.push_back((uint)&ourMesh); //Delete the meshes on cleanup!!!!
			}

		}

		aiReleaseImport(scene);
		mesh_array = m_Entries; //
	}
	else
		LOG("Error loading scene %s", file_path);

	return ret;
}

bool Importer::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
	return false;
}
 
void Importer::Clear()
{
}


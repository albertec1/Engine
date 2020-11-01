#include "Globals.h"
#include "MeshImporter.h"
#include "Assimp.h"
#include "Application.h"

#pragma comment (lib, "assimp.lib")

#include <cmath>

MeshImporter::MeshImporter()
{

}

MeshImporter::~MeshImporter()
{
}

MeshEntry* MeshImporter::LoadSceneMeshes(const std::string& filename)
{
	MeshEntry* ret = nullptr;
	//import the scene from a file
	const char* file_path = filename.c_str(); 

	//Assimp::MeshImporter MeshImporter; //what is this? Could it be a better implementation?
	//const aiScene* scene = MeshImporter.ReadFile(file_path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	LOG("Loading Model from file: %s", file_path);

	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	//Make sure the scene was loaded correct
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (uint i = 0; i < scene->mNumMeshes; ++i)
		{
			ret = ImportMesh(scene, i);
		}
	}
	else
	{
		LOG("No meshes at scene %s", file_path);
	}
	aiReleaseImport(scene);

	return ret;
}

MeshEntry* MeshImporter::ImportMesh(const aiScene* scene, int i)
{	
	bool ret = true;

	MeshEntry* ourMesh = new MeshEntry();
	// New mesh
	aiMesh* currentMesh = scene->mMeshes[i];

	// copy vertices
	//ourMesh->num_vertices = currentMesh->mNumVertices;
	// create a float array with 3 times the size of the number of vertices of the mesh
	//ourMesh->vertices = new float[ourMesh->num_vertices * 3];
	// store into the previously created array the content of the vertices array of the mesh we are loading
	//memcpy(ourMesh->vertices, currentMesh->mVertices, sizeof(float) * ourMesh->num_vertices * 3);
	
	ourMesh->num_vertices = currentMesh->mNumVertices;
	ourMesh->vertices = new fvertex3[ourMesh->num_vertices];
	for (uint i = 0; i < currentMesh->mNumVertices; ++i)
	{
		ourMesh->vertices[i].x = currentMesh->mVertices[i].x;
		ourMesh->vertices[i].y = currentMesh->mVertices[i].y;
		ourMesh->vertices[i].z = currentMesh->mVertices[i].z;
	}
	
	//copy faces
	if (currentMesh->HasFaces())
	{
		//copy number of indices
		ourMesh->num_indices = currentMesh->mNumFaces * 3;
		////create an array with the size of the number of indices
		ourMesh->indices = new uint [ourMesh->num_indices];
		//for each face
		for (uint i = 0; i < currentMesh->mNumFaces; ++i)
		{
			if (currentMesh->mFaces[i].mNumIndices != 3)
			{
				LOG("WARNING, geometry face with != 3 indices!");	
			}
			else
			{
				//copy the 3 face indices into our indices array
				memcpy(&ourMesh->indices[i * 3], currentMesh->mFaces[i].mIndices, 3 * sizeof(uint));
			}
		}
	}	

	if (currentMesh->HasNormals())
	{
		ourMesh->num_normals = currentMesh->mNumVertices;
		ourMesh->normals = new float [currentMesh->mNumVertices * 3];
		memcpy(ourMesh->normals, currentMesh->mNormals, sizeof(float) * ourMesh->num_normals * 3);
	}

	if (currentMesh->HasTextureCoords(0))
	{
		ourMesh->num_tex_coords = scene->mMeshes[i]->mNumVertices;
		ourMesh->texture_coords = new float[scene->mMeshes[i]->mNumVertices * 2];
	
		for (unsigned int j = 0; j < ourMesh->num_tex_coords; ++j)
		{
			ourMesh->texture_coords[j * 2] = currentMesh->mTextureCoords[0][j].x;
			ourMesh->texture_coords[j * 2 + 1] = currentMesh->mTextureCoords[0][j].y;
		}
		LOG("has texture coords: %d", ourMesh->num_tex_coords);
	}
	
	return ourMesh;
}

bool MeshImporter::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
	return false;
}
 
void MeshImporter::Clear()
{
}


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

MeshEntry* Importer::LoadScene(const std::string& filename)
{
	MeshEntry* ret = nullptr;
	//import the scene from a file
	const char* file_path = filename.c_str(); //I use c_str here to prevent accessing weird places if Filename gets deleted or something before getting to this point.
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);

	/*Assimp::Importer Importer; //what is this? Could it be a better implementation?
	const aiScene* pScene = Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);*/

	//Make sure the scene was loaded correctlyafjf
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

	if (scene != nullptr && scene->HasMaterials())
	{
		/*	for (uint i = 0; i < scene->mNumMaterials; ++i)
			{

			}*/
	}
	aiReleaseImport(scene);

	return ret;
}

MeshEntry* Importer::ImportMesh(const aiScene* scene, int i)
{	
	bool ret = true;

	MeshEntry* ourMesh = new MeshEntry;
	// New mesh
	aiMesh* currentMesh = scene->mMeshes[i];
	// copy vertices
	ourMesh->num_vertices = currentMesh->mNumVertices;
	// create a float array with 3 times the size of the number of vertices of the mesh
	ourMesh->vertices = new float[ourMesh->num_vertices * 3];
	// store into the previously created array the content of the vertices array of the mesh we are loading
	memcpy(ourMesh->vertices, currentMesh->mVertices, sizeof(float) * ourMesh->num_vertices* 3);

	LOG("New mesh added with %d vertices", ourMesh->num_vertices);

	//copy faces
	if (currentMesh->HasFaces())
	{
		//copy number of indices
		ourMesh->num_indices = currentMesh->mNumFaces * 3;
		//create an array with the size of the number of indices
		ourMesh->indices = new uint [ourMesh->num_indices];
		//for each face
		for (uint i = 0; i < currentMesh->mNumFaces; ++i)
		{
			if (currentMesh->mFaces->mNumIndices != 3)
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
		ourMesh->num_tex_coords = currentMesh->mNumVertices;
		ourMesh->texture_coords = new float[currentMesh->mNumVertices * 2];

		for (unsigned int i = 0; i < ourMesh->num_tex_coords; i++)
		{
			ourMesh->texture_coords[i * 2] = currentMesh->mTextureCoords[0][i].x;
			ourMesh->texture_coords[i * 2 + 1] = currentMesh->mTextureCoords[0][i].y;
		}
	}

	return ourMesh;
}

bool Importer::InitMaterials(const aiScene* pScene, const std::string& Filename)
{
	return false;
}
 
void Importer::Clear()
{
}


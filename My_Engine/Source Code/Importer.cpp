#include "Globals.h"
#include "Importer.h"
#include "Dependencies/Assimp/include/cimport.h"
#include "Dependencies/Assimp/include/scene.h"
#include "Dependencies/Assimp/include/postprocess.h"

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
	return false;
}

void Mesh::Render()
{
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

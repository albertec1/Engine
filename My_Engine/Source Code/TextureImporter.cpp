#include "TextureImporter.h"
#include "Globals.h"
#include "Application.h"
#include "Assimp.h"
#include <cmath>

#include "Dependencies/glew/include/GL/glew.h"

#include "Dependencies/Devil/include/IL/il.h"
#include "Dependencies/Devil/include/IL/ilu.h"
#include "Dependencies/Devil/include/IL/ilut.h"
#pragma comment( lib, "Devil/libx86/DevIL.lib" )
#pragma comment( lib, "Devil/libx86/ILU.lib" )
#pragma comment( lib, "Devil/libx86/ILUT.lib" )

//Devil

TextureImporter::TextureImporter()
{

}

TextureImporter::~TextureImporter()
{

}

TextureInfo::~TextureInfo()
{
	ilDeleteImages(1, &this->tex_ID);
}

bool TextureImporter::Init()
{
	bool ret = true;

	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION || iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION || iluGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION)
	{
		LOG("ERROR: DevIL version not correct");
		ret = false;
	}

	else
	{
		LOG("Initializing DevIL");

		ilInit();
		iluInit();
		ilutInit();

		ilutRenderer(ILUT_OPENGL);
	}

	return ret;
}

TextureInfo* TextureImporter::LoadSceneTextures(const std::string& filename)
{
	TextureInfo* ret = nullptr;
	//import the scene from a file
	const char* file_path = filename.c_str();

	//Assimp::MeshImporter MeshImporter; //what is this? Could it be a better implementation?
	//const aiScene* scene = MeshImporter.ReadFile(file_path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	LOG("Loading Model from file: %s", file_path);

	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	//Make sure the scene was loaded correctly and has materials to load
	if (scene != nullptr && scene->HasMaterials())
	{
		// Use scene->mNumMeshes to iterate on scene->mMaterials array
		for (uint i = 0; i < scene->mNumMaterials; ++i)
		{
			ret = ImportTexture(scene, i);
		}
	}
	else
		LOG("No materials at scene: %s", file_path);
	aiReleaseImport(scene);

	return ret;
}

TextureInfo* TextureImporter::ImportTexture(const aiScene* pScene, int i)
{
	TextureInfo* tex = new TextureInfo;
	aiMaterial* currentMaterial = pScene->mMaterials[i];

	if (currentMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
		aiString Path;

		if (currentMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
		{
			std::string temp_path = Path.data;
			std::string final_path = "Assets/Textures/";
			final_path.append(temp_path.c_str());

			tex->tex_path = final_path.c_str();
			ILuint ImageName;

			ilGenImages(1, &ImageName);
			ilBindImage(ImageName);

			if (!ilLoadImage(tex->tex_path))
			{
				ILenum Error;
				while ((Error = ilGetError()) != IL_NO_ERROR) {
					LOG("%d: %s/n", Error, iluErrorString(Error));
				}

				LOG("Failed to load Image: %s.", tex->tex_path);
			}
			else
			{
				tex->tex_ID = ilutGLBindTexImage();

				if (ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE));

				tex->tex_width = ilGetInteger(IL_IMAGE_WIDTH);
				tex->tex_height = ilGetInteger(IL_IMAGE_HEIGHT);
				tex->tex_bit_depth = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
				tex->tex_format = ilGetInteger(IL_IMAGE_FORMAT);
				tex->tex_data = ilGetData();

				glGenTextures(1, &tex->tex_ID);

				glBindTexture(GL_TEXTURE_2D, tex->tex_ID);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex->tex_width, tex->tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->tex_data); //which one is better? difference?
				glGenerateMipmap(GL_TEXTURE_2D);
				//gluBuild2DMipmaps(GL_TEXTURE_2D, tex->tex_bit_depth, tex->tex_width, tex->tex_height, tex->tex_format, GL_UNSIGNED_BYTE, tex->tex_data);

				ilDeleteImage(ImageName);
				glBindTexture(GL_TEXTURE_2D, 0);
				return tex;
			}
		}
	}
	return tex;
}

uint* TextureImporter::CheckerImage()
{
	return 0;
}



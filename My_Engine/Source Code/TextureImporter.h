#pragma once

#include "Globals.h"
#include <string>
#include <vector>
<<<<<<< HEAD
#include "Dependencies/Devil/include/IL/ilu.h"


class aiScene;

class TextureInfo
{
public:
	~TextureInfo();

public:
	uint tex_ID;
	const char* tex_path;
	uint tex_width;
	uint tex_height;
	uint tex_bit_depth;
	uint tex_format;
	const void* tex_data = 0;
};

class TextureImporter
{
	public:
	TextureImporter();
	~TextureImporter();

	bool Init();
	uint* CheckerImage();
	TextureInfo* LoadSceneTextures(const std::string& filename);
	TextureInfo* ImportTexture(const aiScene* pScene, int i);
};
=======

class TextureImporter
{
public:

	TextureImporter();
	~TextureImporter();

	uint* CheckerImage();
	uint* LoadTexture();

public:



};

class TextureInfo
{
public:
	uint tex_ID;
	uint tex_width;
	uint tex_height;
	std::string path;
};
>>>>>>> 39d0333f8e22603ea04a1523365e9bdd4ab7442f

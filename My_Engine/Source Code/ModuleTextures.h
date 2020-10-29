#pragma once

#include "Globals.h"
#include <string>
#include <vector>

class TextureImporter
{
public:
	
	TextureImporter();
	~TextureImporter();

	uint* CheckerImage();
	uint* LoadTexture();

public:



};

class Texture
{
public:
	uint textureID;
};
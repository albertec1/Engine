#include "TextureImporter.h"
#include "Globals.h"
#include "Application.h"
#include "Dependencies/Assimp/include/material.h"
#include "Dependencies/Assimp/include/texture.h"

#include <cmath>

#pragma comment( lib, "Devil/libx86/DevIL.lib" )
#include "Dependencies/Devil/include/ilu.h"
#pragma comment( lib, "Devil/libx86/ILU.lib" )
#include "Dependencies\Devil\include\ilut.h"
#pragma comment( lib, "Devil/libx86/ILUT.lib" )

//Devil

TextureImporter::TextureImporter()
{

}

TextureImporter::~TextureImporter()
{

}

uint* TextureImporter::LoadTexture()
{
	return 0;
}

uint* TextureImporter::CheckerImage()
{
	return 0;
}
#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "MeshImporter.h"
#include "TextureImporter.h"
#include <vector>
#include <string>

#define MAX_LIGHTS 8

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
//	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);
	void LoadModel(const std::string& filename);
	TextureInfo* CreateCheckerImage() const;
	

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext gl_context;

	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	std::vector<MeshEntry*> mesh_array;
	std::vector<TextureInfo*> tex_array;


private:

	void LoadBuffer(MeshEntry* mesh);
	void DrawMesh(MeshEntry* mesh);
	void DrawObject(MeshEntry* mesh, TextureInfo* tex);
	void DrawAllMeshes();
	void DrawAllObjects(TextureInfo* tex);

	TextureImporter* tex_imp;
	MeshImporter* mesh_imp;

	TextureInfo* checker_info;

 ////Testinng variables/////
	//float *positions;
	//unsigned int buffer;

};
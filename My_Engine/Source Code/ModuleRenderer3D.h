#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include <vector>
#include <string>

#define MAX_LIGHTS 8

struct MeshEntry;

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);
	void LoadModel(const std::string& filename);
	void Draw(MeshEntry* mesh);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext gl_context;

	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	std::vector<uint> mesh_array;

 ////Testinng variables/////
	//float *positions;
	//unsigned int buffer;

};
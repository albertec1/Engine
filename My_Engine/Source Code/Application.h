#pragma once

#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModulePhysics3D.h"
#include "ModuleMenu.h" 
#include "MeshImporter.h"

#include <list>

class Application
{
public:
	ModuleWindow* window;
	ModuleMenu* menu;
	ModuleInput* input;
	//ModuleAudio* audio;
	ModuleSceneIntro* scene_intro;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModulePhysics3D* physics;
	MeshImporter* imp;


private:

	Timer	ms_timer;
	Timer	fps_timer;
	float	dt;
	std::list<Module*> list_modules;
	bool exit;
	int	miliseconds;
	int contFPS;
	int	last_ms;
	int	last_fps;
	Uint32 frames;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	void OpenBrowser(const char* url) const;
	void Exit();
	uint GetFRLimit() const;
	void SetFRLimit(uint max_framerate);

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();
};
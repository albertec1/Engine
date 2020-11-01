#ifndef __ModuleEditor_H__
#define __ModuleEditor_H__

#include "Module.h"
#include "Globals.h"

class ModuleMenu : public Module
{
public:
	ModuleMenu(Application* app, bool start_enabled = true);
	~ModuleMenu();

	bool Start() override;
	update_status Update(float dt) override;
	bool CleanUp() override;

	void Render();
public:
	bool show_demo_window;
};

#endif //__ModuleEditor_H__

#ifndef __ModuleEditor_H__
#define __ModuleEditor_H__

#include "Module.h"
#include "Globals.h"

class Window;
class Win_Inspector;

class ModuleMenu : public Module
{
public:
	ModuleMenu(Application* app, bool start_enabled = true);
	~ModuleMenu();

	bool Start() override;
	update_status Update(float dt) override;
	bool CleanUp() override;

	void AddWindow(Window* window);
	void Render();
public:
	bool show_demo_window;

	std::vector<Window*> winArray;
	Win_Inspector* inspector = nullptr;
};

#endif //__ModuleEditor_H__

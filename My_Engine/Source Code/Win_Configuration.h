
#include "Window.h"
#include "ImGui.h"
#include <vector>
#include <Globals.h>

class Win_Configuration : public Window
{
public:
	const uint default_w = 325;
	const uint default_h = 417;
	const uint default_x = 956;
	const uint default_y = 609;
public:
	Win_Configuration();
	virtual ~Win_Configuration();

	void Draw() override;

	void AddInput(const char* entry);
	void AddFPS(float fps, float ms);


private:
	ImGuiTextBuffer input_buf;
	bool need_scroll = false;
	std::vector<float> fps_log;
	std::vector<float> ms_log;
};

#include "Window.h"
#include "ImGui.h"
#include <vector>
#include <Globals.h>

#define LOG_LENGTH 50

class Win_Configuration : public Window
{
public:
	const uint default_w = 325;
	const uint default_h = 417;
	const uint default_x = 956;
	const uint default_y = 609;
public:

	Win_Configuration(int _max_fps);
	virtual ~Win_Configuration();

	void Draw() override;
	void CleanUp() override;

	void AddInput(const char* entry);
	void AddLogFPS(float fps, float ms);

	bool changeFPSlimit = false;
	int max_fps = 60;

private:
	ImGuiTextBuffer input_buf;
	bool need_scroll = false;
	std::vector<float> fps_log;
	std::vector<float> ms_log;
};
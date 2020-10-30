
#include "Window.h"
#include "ImGui.h"

class Win_Console : public Window
{
public:
	Win_Console(bool _active);
	virtual ~Win_Console();

	void Draw() override;

	void CleanUp();
	void AddLog(const char* entry);

private:

	ImGuiTextBuffer buffer;
	bool scrollToBottom = true;
};
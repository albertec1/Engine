#include "Win_Console.h"

Win_Console::Win_Console(bool _active) : Window(_active)
{}
	
Win_Console::~Win_Console()
{}

void Win_Console::CleanUp()
{
	buffer.clear();
}

void Win_Console::AddLog(const char* entry)
{
	buffer.appendf(entry);
	scrollToBottom = true;
}

void Win_Console::Draw()
{
	if (!active)
		return;
	if (ImGui::Begin("Console", &active))
	{
		ImGui::TextUnformatted(buffer.begin());
		if (scrollToBottom)
		{
			ImGui::SetScrollHere(1.0f);
		}

		scrollToBottom = false;
	}
	ImGui::End();

}
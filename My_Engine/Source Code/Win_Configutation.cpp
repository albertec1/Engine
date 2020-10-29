
#include "Application.h"
#include "Win_Configuration.h"
#include "ImGui.h"
#include "ModuleWindow.h"
#include "Color.h"

using namespace std;

// ---------------------------------------------------------
Win_Configuration::Win_Configuration() : Window("Configuration"),
fps_log(100), ms_log(100)
{}

Win_Configuration::~Win_Configuration()
{}

void Win_Configuration::Draw()
{
	//ImGui::Begin("Configuration", &active, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoFocusOnAppearing);
	if (!active)
		return;

	if (ImGui::Begin("Configuration", &active))
	{
		if (ImGui::CollapsingHeader("Application"))
		{
			int max_fps = App->GetFRLimit();
			if (ImGui::SliderInt("Max FPS", &max_fps, 0, 120))
				App->SetFRLimit(max_fps);

			ImGui::Text("Limit Framerate:");
			ImGui::SameLine();
			ImGui::TextColored(YELLOW, "%i", App->GetFramerateLimit());

			char title[25];
			sprintf_s(title, 25, "Framerate %.1f", fps_log[fps_log.size() - 1]);
			ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
			sprintf_s(title, 25, "Milliseconds %0.1f", ms_log[ms_log.size() - 1]);
			ImGui::PlotHistogram("##milliseconds", &ms_log[0], ms_log.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));
		}
		ImGui::End();
	}
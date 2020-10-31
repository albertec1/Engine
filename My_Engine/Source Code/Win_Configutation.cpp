
#include "Win_Configuration.h"
#include "ImGui.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "Color.h"
#include "Globals.h"

// ---------------------------------------------------------
Win_Configuration::Win_Configuration(int _max_fps) : Window("Configuration"),
fps_log(LOG_LENGTH), ms_log(LOG_LENGTH)
{}

Win_Configuration::~Win_Configuration()
{}

void Win_Configuration::CleanUp()
{
}


void Win_Configuration::AddLogFPS(float fps, float ms)
{
	static uint count = 0;

	if (count == LOG_LENGTH)
	{
		for (uint i = 0; i < LOG_LENGTH - 1; ++i)
		{
			fps_log[i] = fps_log[i + 1];
			ms_log[i] = ms_log[i + 1];
		}
	}
	else
		++count;

	fps_log[count - 1] = fps;
	ms_log[count - 1] = ms;
}

void Win_Configuration::Draw()
{
	if (!active)
		return;

	if (ImGui::Begin("Configuration", &active))
	{
		if (ImGui::CollapsingHeader("Application"))
		{
			char appName[100];
			strcpy_s(appName, 100, App->GetTitleName());

			if (ImGui::InputText("Project Name", appName, 100, ImGuiInputTextFlags_EnterReturnsTrue))
			{
				App->SetTitleName(appName);
			}

			if (ImGui::SliderInt("Max FPS", &max_fps, 0, 140))
			{
				changeFPSlimit = true;
			}


			ImGui::Text("Limit Framerate:");
			ImGui::SameLine();
			ImGui::TextColored(YELLOW, "%i", max_fps);

			char title[25];
			sprintf_s(title, 25, "Framerate %.1f", fps_log[fps_log.size() - 1]);
			ImGui::PlotHistogram("##framerate", &fps_log[0], fps_log.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
			sprintf_s(title, 25, "Milliseconds %0.1f", ms_log[ms_log.size() - 1]);
			ImGui::PlotHistogram("##milliseconds", &ms_log[0], ms_log.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));



		}
		if (ImGui::CollapsingHeader("Render"))
		{
			/*bool enabled = App->renderer3D->depthEnabled;
			if (ImGui::Checkbox("Depth Buffer", &enabled))
			{
				App->renderer3D->SetDepthBufferEnabled(enabled);
			}*/
			if (ImGui::Checkbox("Depth Buffer", &App->renderer3D->depthEnabled))
			{ 
				App->renderer3D->SetDepthBufferEnabled();
			}
			if (ImGui::Checkbox("Wireframe Mode", &App->renderer3D->wireframeMode)) {}
	
			bool vsync = App->renderer3D->GetVSync();
			if (ImGui::Checkbox("Vertical Sync", &vsync))
			{
					changeFPSlimit = true;
					App->renderer3D->SetVSync(vsync);
			}
			
		}
		if (ImGui::CollapsingHeader("Input"))
		{
			ImGui::Text("Mouse position: %i, %i", App->input->GetMouseX(), App->input->GetMouseY());
			ImGui::Text("Mouse motion: %i, %i", App->input->GetMouseXMotion(), App->input->GetMouseYMotion());
			ImGui::Text("Mouse wheel: %i", App->input->GetMouseZ());
		}
		if (ImGui::CollapsingHeader("Window"))
		{
			int w = App->window->GetWidth();
			int h = App->window->GetHeight();
			if (ImGui::SliderInt("Width", &w, 0, 1920)) { App->window->SetWidth(w); }
			if (ImGui::SliderInt("Height", &h, 0, 1080)) { App->window->SetHeight(h); }
		}

		ImGui::End();
	}
}
#include "Application.h"
#include "ModuleMenu.h"

#include "ImGui.h"	


ModuleMenu::ModuleMenu(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleMenu::~ModuleMenu()
{
}

bool ModuleMenu::Start()
{
	LOG("Init Editor");

	//Set all the atributes and flags for our Gui window
	const char* glsl_version = "#version 130";

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 7.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Our state
	show_demo_window = true;

	// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->gl_context);
	ImGui_ImplOpenGL3_Init(glsl_version);

	return true;
}

bool ModuleMenu::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}

update_status ModuleMenu::Update(float dt)
{

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	//Top bar menu, with an option to close the editor
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Options"))
		{
			if (ImGui::MenuItem("Close", "Alt+F4")) { return UPDATE_STOP; }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Gui Demo")) {}

			if (ImGui::MenuItem("Documentation"))
					App->OpenBrowser("https://github.com/albertec1/Yet-another-janky-Engine/wiki");

			if (ImGui::MenuItem("Download latest"))
					App->OpenBrowser("https://github.com/albertec1/Yet-another-janky-Engine/releases");

			if (ImGui::MenuItem("Report a bug"))
					App->OpenBrowser("https://github.com/albertec1/Yet-another-janky-Engine/issues");

			ImGui::EndMenu();
			}
		ImGui::EndMenuBar();
		ImGui::End();
	}

	//Window with a checkbox allowing to show the demo window of ImGui
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);
	{
		ImGui::Begin("DEMO");
		ImGui::Checkbox("Demo Window", &show_demo_window);		
	}

	return UPDATE_CONTINUE;
}

void ModuleMenu::Render()
{
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}
}

#include "Application.h"
#include "ModuleMenu.h"

#include "Dependencies/ImGUI/imgui.h"
#include "Dependencies/ImGUI/imgui_internal.h"
#include "Dependencies/ImGUI/imgui_impl_sdl.h"
#include "Dependencies/ImGUI/imgui_impl_opengl3.h"
		  
#include "Dependencies/glew/include/GL/glew.h"
#include "Dependencies/SDL/include/SDL_opengl.h"


ModuleMenu::ModuleMenu(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleMenu::~ModuleMenu()
{
}

bool ModuleMenu::Start()
{
	LOG("Init Editor");

	//Initialize glew
	GLenum err = glewInit();
	LOG("Using Glew %s", glewGetString(GLEW_VERSION));

	LOG("Vendor: %s", glGetString(GL_VENDOR));
	LOG("Renderer: %s", glGetString(GL_RENDERER));
	LOG("OpenGL version supported: %s", glGetString(GL_VERSION));
	LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	//Set all the atributes and flags for our Gui window
	const char* glsl_version = "#version 130";

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	ImGui::StyleColorsDark();

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

		ImGui::End();
	}

	return UPDATE_CONTINUE;
}

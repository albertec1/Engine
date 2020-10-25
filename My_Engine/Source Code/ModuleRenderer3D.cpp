#include "Application.h"
#include "ModuleRenderer3D.h"
#include "Importer.h"

#include <iostream>

#include "ImGui.h"
#include "OpenGl.h"
#include "Assimp.h"

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

//static unsigned int CompileShader(unsigned int type, const std::string& source)
//{
//	unsigned int id = glCreateShader(GL_VERTEX_SHADER);
//	const char* src = source.c_str();
//	glShaderSource(id, 1, &src, nullptr);
//	glCompileShader(id);
//
//	int result;
//	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
//	if (result == GL_FALSE)
//	{
//		int length;
//		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
//		char* message = (char*)alloca(length * sizeof(char));
//		glGetShaderInfoLog(id, length, &length, message);
//		LOG("Failed to compile shader!");
//		LOG(message);		
//
//		glDeleteShader(id);
//		return 0;
//	}
//
//	return id;
//}
//
//static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
//{
//	unsigned int program = glCreateProgram();
//	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
//	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//	glAttachShader(program, vs);
//	glAttachShader(program, fs);
//	glLinkProgram(program);
//	glValidateProgram(program);
//
//	glDeleteShader(vs);
//	glDeleteShader(fs);
//
//	return program;
//}

ModuleRenderer3D::ModuleRenderer3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	LOG("Creating 3D Renderer context");
	bool ret = true;

	//Create context
	gl_context = SDL_GL_CreateContext(App->window->window);
	if(gl_context == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	
	GLenum error = glewInit();

	if (error != GL_NO_ERROR)
	{
		LOG("Error initializing glew library! %s", SDL_GetError());
		ret = false;
	}

	if(ret == true)
	{
		//Use Vsync
		if(VSYNC && SDL_GL_SetSwapInterval(1) < 0)
		LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());

		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error..1
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error..2
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		//Initialize clear color
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Check for error..3
		error = glGetError();
		if (error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
		
		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();
		lights[0].Active(true);
		
		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);
		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
	}

	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	//temporary till i figure ou where to put it
	LoadModel("Models/warrior.FBX");

	// Projection matrix for
	OnResize(SCREEN_WIDTH, SCREEN_HEIGHT);
	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	//recalculate projection matrix and set up the viewport if the window resizes?

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());

	// light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	//loop de la lista de modelos y Draw()
	//glDrawElements(GL_TRIANGLES, m_Entries[i].NumIndices, GL_UNSIGNED_INT, 0);

//DIRECT MODE TRIANGLE EXAMPLE//JUST TO CHECK IT IS WORKING PROPERLY
	//glLineWidth(2.0f);
	//glBegin(GL_TRIANGLES);
	//
	//glVertex3f(-5.f, 1.f, 0.f);
	//glVertex3f( 5.f, 1.f, 0.f);
	//glVertex3f( 0.f, 6.f, 0.f);
	//
	//glEnd();
	//glLineWidth(1.0f);
	//////

	return UPDATE_CONTINUE;
}

update_status ModuleRenderer3D::Update(float dt)
{
	
//EXAMPLE////////////////////////
	//float pArr[6]
	//{
	//	-0.5f, -0.5f,
	//     0.0f,  0.5f,
	//	 0.5f, -0.5f
	//};
	//positions = pArr;
	//glGenBuffers(1, &buffer);
	//glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(byte) * 6, positions, GL_STATIC_DRAW);
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	//std::string vertexShader =
	//	"#version 330 core\n"
	//	"\n"
	//	"layout(location = 0) in vec4 position;"
	//	"\n"
	//	"void main()\n"
	//	"{\n"
	//	"	gl_Position = position;\n"
	//	"}\n";
	//std::string fragmentShader =
	//	"#version 330 core\n"
	//	"\n"
	//	"layout(location = 0) out vec4 color;"
	//	"\n"
	//	"void main()\n"
	//	"{\n"
	//	"color = vec4(0.1, 0.0, 0.0, 0.1);\n"
	//	"}\n";
	//unsigned int shader = CreateShader(vertexShader, fragmentShader);
	//glUseProgram(shader);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	//SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
	//SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
	//SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	//
	//glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);

	DrawAllMeshes();
	//ImGui Render
	App->menu->Render();

	
	SDL_GL_SwapWindow(App->window->window);

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	// detach log stream
	aiDetachAllLogStreams();

	LOG("Destroying 3D Renderer");

	SDL_GL_DeleteContext(gl_context);

	return true;
}


void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

MeshEntry* ModuleRenderer3D::LoadModel(const std::string& filename)
{
	Importer imp;
	MeshEntry* temp = imp.LoadScene(filename);
	LoadBuffer(temp);
	mesh_array.push_back(temp);
	return temp;
}

void ModuleRenderer3D::LoadBuffer(MeshEntry* mesh)
{
	//Create a vertex array object which will hold all buffer objects
	glGenVertexArrays(1, &mesh->VAO);
	glBindVertexArray(mesh->VAO);

	if (mesh->num_vertices > 0)
	{
		glGenBuffers(1, (GLuint*)&mesh->b_vertices);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->b_vertices);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->num_vertices * 3, mesh->vertices, GL_STATIC_DRAW);
	}

	if (mesh->num_indices > 0)
	{
		glGenBuffers(1, (GLuint*)&mesh->b_indices);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->b_indices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * mesh->num_indices, mesh->indices, GL_STATIC_DRAW);

		//Set the vertex attrib pointer
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}
	if (mesh->num_tex_coords > 0) // tex_coords ///////////
	{
		glGenBuffers(1, (GLuint*)&mesh->b_indices);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->b_indices);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->num_tex_coords * 2, mesh->texture_coords, GL_STATIC_DRAW);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
	}
	if (mesh->num_indices > 0) // normals ////////////
	{
		glGenBuffers(1, (GLuint*)&mesh->b_normals);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->b_normals);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->num_normals * 3, mesh->normals, GL_STATIC_DRAW);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(2);
	}

	glBindVertexArray(0);
	
}

void ModuleRenderer3D::DrawMesh(MeshEntry* mesh)
{
	
	
	glBindVertexArray(mesh->VAO);
	glDrawElements(GL_TRIANGLES, mesh->num_indices, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	
}

void ModuleRenderer3D::DrawAllMeshes()
{	
	for (int m = 0; m < mesh_array.size(); m++)
	{
		DrawMesh(mesh_array[m]);
	}
}
           
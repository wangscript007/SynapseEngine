#include "VirtualWarApp.h"
#include "EngineGlobal.h"
#include "EditorMainState.h"
#include "UserInput.h"
#include "Physics.h"
#include "SoundEngine.h"

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

int VirtualWarApp::rWidth = 0;
int VirtualWarApp::rHeight = 0;


VirtualWarApp::VirtualWarApp() {



}

void VirtualWarApp::BeginGame() {

	gWidth = 1024;
	gHeight = 768;
	gFullscreen = false;

	CreateMainWindow();
	std::cout << "Game starting.\n";

	gRunning = true;

	while (gRunning) {

	}


}

void VirtualWarApp::PushState(AppState* state)
{
	//main->GetStates()
	Main->states.push_back(state);
	state->InitState();

}

VirtualWarApp* VirtualWarApp::Main = NULL;

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{

	UI::SetMouse(xpos, ypos, 0);

	VirtualWarApp::Main->SetMouse(xpos, ypos,0);


}

void VirtualWarApp::SetMouse(float x, float y, float z) {

	AppState* cs = states.back();

	UserInput::main->SetMouse(x, y, z);

	//cs->SetMouse(x, y, z);



}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			UI::SetMouseBut(0, true);
			UserInput::main->SetButton(0, true);
		}
		else {
			UI::SetMouseBut(0, false);
			UserInput::main->SetButton(0, false);
		}
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {

		if (action == GLFW_PRESS) {
			UI::SetMouseBut(1, true);
			UserInput::main->SetButton(1, true);
		}
		else {
			UI::SetMouseBut(1, false);
			UserInput::main->SetButton(1, false);
		}

	}
	
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
	if (action == GLFW_PRESS) {
		VirtualWarApp::Main->SetKey(key, true);
	}
	else if(action == GLFW_RELEASE) {
		VirtualWarApp::Main->SetKey(key, false);
	}
	printf("KeyPress:%d\n", key);

}


void VirtualWarApp::SetKey(int key, bool state) {

	AppState* cs = states.back();

	UserInput::main->SetKey(key, state);

	//cs->SetKey(key, state);



}

void VirtualWarApp::BeginEditor() {

	gWidth = 1024;
	gHeight = 768;
	rWidth = gWidth;
	rHeight = gHeight;
	gFullscreen = false;
	Main = this;

	EngineGlobals::rWidth = gWidth;
	EngineGlobals::rHeight = gHeight;

	CreateMainWindow();
	std::cout << "Editor starting.\n";

	gRunning = true;

	//FTFont::InitFontLib();
	

	EditorFont = new kFont("data/font/basic.pf");

//	glClearColor(0, 0,0, .0f);
	glViewport(0, 0, gWidth, gHeight);
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glDisable(GL_SCISSOR_TEST);

	draw = new IDraw(gWidth, gHeight);

	WhiteTex = new Texture2D("edit/tex/white.png", false);

	UserInput* input = new UserInput;

	Physics* physics = new Physics;

	EditorMainState* state1 = new EditorMainState();

	SoundEngine* soundEngine = new SoundEngine;

	PushState(state1);



	UI::UIFont = EditorFont;
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);
	lfps = clock();
	while (gRunning) {
		glfwPollEvents();
	//	glClear(0, 1, 1, 1);
		int t = clock();

		if (t > (lfps + 1000)) {

			fps = frame;
			frame = 0;
			lfps = t;
			printf("FPS:%d\n", fps);
		}
		frame++;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		AppState* cs = states.back();


		cs->UpdateState();



//		draw->Begin();

		//draw->DrawTex(20, 20, 200, 200, WhiteTex, 1, 1, 1, 1);

		//draw->End();

		glClear(GL_DEPTH_BUFFER_BIT);

	//	EditorFont->Drpha.",5,35);

		EditorFont->drawText("Virtual>War - Pre-Alpha test 0.01a.", 5, 5, 1, 1, 1, 1);

		cs->RenderState();

		glfwSwapBuffers(window);

		//

	}

}

void VirtualWarApp::CreateMainWindow() {

	if (!glfwInit())
	{
		// Initialization failed
		std::cout << "Failed to initialize glfw.\n";
	}
	else {

		std::cout << "Window created.\n";
			
	}
	glfwSetErrorCallback(error_callback);

//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	 window = glfwCreateWindow(gWidth,gHeight, "Virtual War", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create glfw window.\n";
		// Window or OpenGL context creation failed
	}

	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
//	glfwSwapInterval(0);

}
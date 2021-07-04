#pragma once
//#include "WindowsIncludes.h"

#include "GameIncludes.h"
#include "kFont.h"
#include "FXTextDraw.h"
#include "AppState.h"
#include <vector>
#include "UI.h"





class VirtualWarApp
{
public:

	VirtualWarApp();

	void CreateMainWindow();

	void BeginGame();
	void BeginEditor();
	void BeginState(AppState* state);
	void SetMouse(float x, float y, float z);
	void SetKey(int key, bool state);



	static void PushState(AppState* state);
	static void PopState();
	std::vector<AppState*> GetStates() {
		return states;
	}

	static VirtualWarApp* Main;
	//static AppState* InitialState;
	static int rWidth, rHeight;
	std::vector<AppState*> states;
private:
	int gWidth, gHeight;
	bool gFullscreen;
	bool gRunning;
	GLFWwindow* window;
	//FTFont* EditorFont;
	kFont* EditorFont;
	IDraw* draw;
	Texture2D* WhiteTex;
	FXTextDraw* FXText;
	int lfps=0;
	int fps=0;
	int frame = 0;

	bool CLInit = false;


};


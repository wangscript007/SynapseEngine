#pragma once
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

enum PadButton {

	A,B,X,Y,Start,Options,Up,Down,Left,Right,LeftShoulder,RightShoulder,LeftStick,RightStick

};

class ControlInput
{
public:
	ControlInput() {


		ZeroMemory(&state, sizeof(XINPUT_STATE));

	
	}

	bool IsPressed(PadButton button)
	{
		return false;

	}

	void Update() {

		ZeroMemory(&state, sizeof(XINPUT_STATE));
	
		

	}
	XINPUT_STATE state;
	float leftStickX, leftStickY;
	float rightStickX, rightStickY;
	float leftTrigger, rightTrigger;
	float deadzoneX = 0.05f;
	float deadzoneY = 0.02f;
};



#pragma once
class UserInput
{
public:

	UserInput() {

		key = new bool[255];
		button = new bool[32];
		mx = 0;
		my = 0;
		mz = 0;
		for (int i = 0; i < 255; i++) {
			key[i] = false;
		}
		for (int i = 0; i < 32; i++) {
			button[i] = false;
		}
		main = this;

	}

	void SetKey(int keyid, bool state) {

		key[keyid] = state;

	}

	void SetMouse(float x, float y, float z) {

		if (first) {

			lx = x;
			ly = y;
			lz = z;
			first = false;
		}

		mx = x - lx;
		my = y - ly;
		mz = z - lz;

		mxp = x;
		myp = y;

		lx = x;
		ly = y;
		lz = z;

	}

	void SetButton(int b, bool state) {
		button[b] = state;
	}

	bool GetButton(int b) {

		return button[b];

	}

	float MouseX() {
		return mxp;
	}

	float MouseY() {
		return myp;
	}

	float MouseMoveX() {
		return mx;
	}

	float MouseMoveY() {
		return my;
	}

	bool KeyDown(int keyid) {

		return key[keyid];

	}
	static UserInput* main;

private:
	
	bool* key;
	bool* button;
	float mxp, myp;
	float mx, my, mz;
	float lx, ly, lz;
	bool first = true;

};


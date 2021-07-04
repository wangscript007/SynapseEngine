#pragma once
class AppState
{
public:

	virtual void SetMouse(float x, float y, float z) {};
	virtual void SetKey(int key, bool state) {};
	virtual void InitState() {};
	virtual void UpdateState() {};
	virtual void RenderState() {};

private:
};


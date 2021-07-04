#pragma once
#include "UIControl.h"
#include "Texture2D.h"
class BoolControl :
    public UIControl
{
public:
    BoolControl();
    void Render();
    void MouseDown(int b);
    void SetStateAct(std::function<void(bool b)> sc) {
        StateChange = sc;
    }
    void SetState(bool b) {
        State = b;
    }
    bool GetState() {
        return State;
    }
    void SetIcon(Texture2D* icon) {
        Icon = icon;
    }
private:
    bool State = false;
    Texture2D* White;
    std::function<void(bool v)> StateChange;
    Texture2D* Icon = NULL;
};


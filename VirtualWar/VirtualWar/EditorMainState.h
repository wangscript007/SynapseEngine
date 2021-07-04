#pragma once
#include "AppState.h"
#include "UI.h"
#include "ButtonControl.h"
#include "ImageControl.h"
#include "BoolControl.h"
class EditorMainState :
    public AppState
{
public:

    void InitState();
    void UpdateState();
    void RenderState();

private:
    UI* ui;

};


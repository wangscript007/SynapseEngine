#pragma once
#include "AppState.h"
#include "UI.h"
#include "ButtonControl.h"
#include "ImageControl.h"
#include "BoolControl.h"
#include "GameWorld.h"
#include "SoundEngine.h"
#include "SoundSource.h"
#include "SoundChannel.h"
class StateIntroLogos :
    public AppState
{
public:

    void InitState();
    void RenderState();

private:

    UI* ui;
    float bgAlpha = 0.0f;
    float syAlpha = 0.0f;
    float enAlpha = 0.0f;
    ImageControl* bar1,* bar2;
    ImageControl* cbg;
    ImageControl* clogo1;
    ImageControl* clogo2;
    SoundSource* logoTrack;
    bool f1 = false;
    float lx = 0;
    SoundChannel* logoChan;
};


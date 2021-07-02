#pragma once
#include "GamePlayer.h"
class PlayerFirstPerson :
    public GamePlayer
{
public:

    PlayerFirstPerson(float height, float radius);
    void UpdateInput();

private:
    float lookY = 0.0f;

};


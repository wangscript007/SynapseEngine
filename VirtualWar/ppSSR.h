#pragma once
#include "kPostProcess.h"
#include "kFrameBuffer.h"
#include "NodeCam.h"
class ppSSR :
    public kPostProcess
{
public:
    ppSSR();

    void SetMaps(std::vector<kFrameBuffer*> ms);
    Texture2D* process(Texture2D* base);

    NodeCam* cam;

private:
    kEffect* ssrFinal;
    kFrameBuffer* fb1 = NULL;
    kFrameBuffer* fb2 = NULL;
    std::vector<kFrameBuffer*> maps;
};


// SpaceBiem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "scenes\bmMenuScene.h"

using biemgine::bmEngine;
using spacebiem::bmMenuScene;

int main()
{
    bmEngine* engine = nullptr;

    try
    {
        engine = new bmEngine;
        engine->start<bmMenuScene>("SpaceBiem v0.1");
    }
    catch (...)
    {
        printf("An unexpected error occured..");
        system("pause");
    }

    delete engine;

    return _CrtDumpMemoryLeaks();
}


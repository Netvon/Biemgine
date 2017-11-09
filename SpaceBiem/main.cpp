// SpaceBiem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "scenes\MenuScene.h"

using biemgine::Engine;
using spacebiem::MenuScene;

int main()
{
    Engine* engine = nullptr;

    try
    {
        engine = new Engine;
        engine->start<MenuScene>("SpaceBiem");
    }
    catch (...)
    {
        printf("An unexpected error occured..");
        system("pause");
    }

    delete engine;

    return _CrtDumpMemoryLeaks();
}


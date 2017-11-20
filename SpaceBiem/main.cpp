// SpaceBiem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "scenes\MenuScene.h"

using biemgine::Engine;
using biemgine::Size;
using spacebiem::MenuScene;

int main()
{
    Engine* engine = nullptr;

    try
    {
        engine = new Engine;
        engine->start<MenuScene>("SpaceBiem", Size{ 1920, 1080 }, false);
    }
    catch (...)
    {
        printf("An unexpected error occured..");
        system("pause");
    }

    delete engine;

    return _CrtDumpMemoryLeaks();
}


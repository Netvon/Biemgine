// SpaceBiem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "scenes\MenuScene.h"

using biemgine::Engine;
using biemgine::Size;
using spacebiem::MenuScene;

int main()
{
    try
    {
        Engine engine;
        engine.start<MenuScene>("SpaceBiem", Size{ 1920, 1080 }, true);
    }
    catch (...)
    {
        printf("An unexpected error occured..");
        system("pause");
    }

    return _CrtDumpMemoryLeaks();
}

// SpaceBiem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "scenes\MenuScene.h"

using biemgine::Engine;
using biemgine::Size;
using biemgine::Thread;
using spacebiem::MenuScene;

int hallo(void* data) {
    auto h = 'a';

    while (true) {
        h++;
    }

    return 2;
}

int main()
{
    try
    {
        //Thread thread{ "test_thread", hallo };

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

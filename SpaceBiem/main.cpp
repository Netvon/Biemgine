// SpaceBiem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "scenes\MenuScene.h"
#include "globals\Ads.h"

using biemgine::Engine;
using biemgine::Size;
using spacebiem::MenuScene;

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    try
    {
        Ads::instance().initialize("ads", ".jpg");

        Engine engine;
        engine.start<MenuScene>("SpaceBiem", Size{ 1920, 1080 }, false);
    }
    catch (...)
    {
        printf("An unexpected error occured..");
        system("pause");
    }

    Ads::instance().close();

    return 0;
}

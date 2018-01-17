// SpaceBiem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "scenes\MenuScene.h"
#include "globals\Ads.h"
#include "scenes/ProfileScene.h"

using biemgine::Engine;
using biemgine::Size;
using spacebiem::ProfileScene;

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    try
    {
        Ads::instance().initialize("ads", ".jpg");

        Engine engine;
        engine.start<ProfileScene>("SpaceBiem", Size{ 1920, 1080 }, false);
    }
    catch (...)
    {
        printf("An unexpected error occured..");
        system("pause");
    }

    Ads::instance().close();

    return 0;
}

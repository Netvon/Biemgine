// SpaceBiem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using biemgine::bmEngine;

int main()
{
    bmEngine* engine = nullptr;

    try
    {
        engine = new bmEngine;
        engine->start("SpaceBiem v0.1");
    }
    catch (...)
    {
        printf("An unexpected error occured..");
        system("pause");
    }

    delete engine;

    return _CrtDumpMemoryLeaks();
}


// SpaceBiem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
    bmEngine* engine = nullptr;

    try
    {
        engine = new bmEngine;
        engine->start();
    }
    catch (...)
    {
        printf("An unexpected error occured..");
        system("pause");
    }

    delete engine;

    return _CrtDumpMemoryLeaks();
}


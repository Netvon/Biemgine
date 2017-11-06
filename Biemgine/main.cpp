#include "stdafx.h"
#include "bmEngine.h"

int main(int argc, char* args[])
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


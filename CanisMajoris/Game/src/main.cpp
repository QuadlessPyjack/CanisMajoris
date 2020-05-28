#include<iostream>
#include "Engine.h"

int main(int argc, char* argv[])
{
    Core::Engine engine;
    engine.Init();
    engine.Run();
    engine.Shutdown();
}
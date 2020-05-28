#include "Engine.h"

#include "EngineImpl.h"

Core::Engine::Engine()
{
    m_engine = std::make_shared<EngineImpl>();
}

void Core::Engine::Init()
{
    m_engine->Init();
}

void Core::Engine::Run()
{
    m_engine->Run();
}

int Core::Engine::Shutdown()
{
    m_engine->Shutdown();
    return 0;
}

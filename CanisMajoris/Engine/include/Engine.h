#ifndef ENGINE_PUBLIC_H_
#define ENGINE_PUBLIC_H_

#include "EngineDllExport.h"

#include <memory>

namespace Core {

    class EngineImpl;

    class CM_ENGINE_API Engine
    {
    public:
        Engine();
        void Init();
        void Run();
        int Shutdown();
    private:
        std::shared_ptr<EngineImpl> m_engine;
    };
}

#endif // ENGINE_PUBLIC_H_
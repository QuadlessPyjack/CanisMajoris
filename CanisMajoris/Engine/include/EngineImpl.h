#ifndef ENGINEIMPL_H_
#define ENGINEIMPL_H_

#include"Events/EventManager.h"
#include"Events/EventClient.h"
#include"Events/TestEventClient.h"

#include"Physics/SimplePhysBody.h"
#include"Physics/PhysicsManager.h"

#include"Editor/ProcyonServer/EditorServer.h"

#include"Utils/MeshContainer.h"
#include"Renderer/CoreUtils/Scene.h"

#include <vector>

struct SDL_Surface;
union SDL_Event;

namespace Core {
    namespace Renderer
    {
        namespace CoreUtils
        {
            class Camera;
            class Rasterizer;
            class Mesh;
            class Triangle;
            class Vertex;
            class Edge;
            class Rasterizer;
        }
    }
    class EngineImpl
    {
    public:
        EngineImpl();
        void Init();
        void Run();
        int Shutdown();
    private:
        std::vector<Renderer::CoreUtils::Vertex*> m_vertexPool;
        std::vector<Renderer::CoreUtils::Edge*> m_edgePool;
        std::vector<Renderer::CoreUtils::Triangle*> m_trianglePool;
        Renderer::CoreUtils::Camera* m_sceneCamera;
        Renderer::CoreUtils::Rasterizer* m_testRasterizer;
        uint8_t* m_keystates;
        bool m_shouldQuit = false;
        SDL_Event m_event;
        Renderer::CoreUtils::Scene& m_mainScene;
        MeshContainer m_meshPool;
        MeshContainer m_meshPool2;
        double m_frame_delta;
        SDL_Surface* m_screen;
        EventClientTest* m_evTest;
        EventClientTest* m_evReceiver;
        Core::EventSys::Event* m_testEvent;
        Editor::ProcyonServer& m_dbgServer;

        int m_eventID;
    };
} // Core

#endif // ENGINEIMPL_H_
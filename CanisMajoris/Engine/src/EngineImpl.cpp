#include "EngineImpl.h"
#include "Renderer/CoreUtils/Rasterizer/Rasterizer.h"
#include "Renderer/CoreUtils/Camera.h"
#include "Renderer/CoreUtils/Scene.h"
#include "FileIO/OBJImpex/Reader/IO_OBJLoader.h"
#include "Utils/Math/ConverterUtils.inl"
#include "Utils/Constants.h"
#include "Utils/Math/Vector2.h"
#include "Editor/ProcyonServer/EditorServer.h"
#include "Editor/ProcyonServer/ProcyonConstants.h"

#include<iostream>
#include<SDL.h>
#include<SDL_draw.h>
#include<SDL_ttf.h>

//For debug purposes only!
#include<chrono>
#include<time.h>

//#include<boost/interprocess/windows_shared_memory.hpp>
//#include<boost/interprocess/mapped_region.hpp>

namespace Core {
	EngineImpl::EngineImpl()
		: m_mainScene(Scene::GetInstance())
		, m_dbgServer(Editor::ProcyonServer::GetInstance())
	{
	}

	void EngineImpl::Init()
    {
		SDL_Init(SDL_INIT_EVERYTHING);
		TTF_Init();
		TTF_Font* dbg_font = nullptr;
		dbg_font = TTF_OpenFont("ARLRDBD.TTF", 20);

		SDL_Surface* dbg_screen = nullptr;
		SDL_Color color = { 255, 255, 255 };
		//dbg_screen = TTF_RenderText_Solid(dbg_font, "Canis Majoris On-Screen Debug Text", color);

		//TTF_RenderText_Solid

		m_screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
		SDL_WM_SetCaption("CANIS MAJORIS 3D PERSPECTIVE", nullptr);

		using namespace std;
		using namespace Core::Renderer::CoreUtils;
		using namespace Core::IO;
		using namespace boost::interprocess;

		m_evTest = new EventClientTest();
		m_evReceiver = new EventClientTest();
		m_testEvent = new Core::EventSys::Event();

		m_testEvent->eventType = 666;
		m_eventID = -10;
		m_evTest->RegisterEvent(m_testEvent, m_eventID);
		cout << "evTest ID: " << m_evTest->clientID() << '\n';
		std::cout << "Event ID is: " << m_eventID << '\n';
		m_evReceiver->ConnectToEvent(m_eventID);
		cout << "receiver ID: " << m_evReceiver->clientID() << '\n';
		/*windows_shared_memory shm(create_only, "DBG_LOG_MEM", read_write, 1000);

		mapped_region region(shm, read_write);
		std::memset(region.get_address(), 'X', region.get_size());*/

		cout << "Lets build a ModelFile and load our test model.\n";
		ModelFile* testOBJ = new ModelFile();
		ModelFile* testOBJ2 = new ModelFile();
		//testOBJ->ExtractVertexData();
		m_dbgServer.InitializeEditorServer();
		m_dbgServer.LogInfo("THIS IS A TEST MESSAGE\n");
		//dbgServer.LogInfo(SHARED_MEMORY_CLEAR);

		cout << "Lets test Vector2 in Polar and Cartesian systems.\n";
		Vector2 testvect2(4, 12);
		cout << "TESTVECT2(4, 12): " << testvect2 << endl;
		testvect2.ToPolar();
		cout << "Polar Conversion: " << testvect2 << endl;
		testvect2.ToCartesian();
		cout << "Now back to Cartesian: " << testvect2 << endl;

		cout << "Lets test Vector3 Addition.\n";
		Vector3 testvect3(1, 2, 3);
		Vector3 testvect4(4, 5, 6);
		Vector3 sum = testvect3 + testvect4;
		cout << "(1,2,3) + (4,5,6) = " << sum << endl;

		cout << "Lets test Vector3 Substraction.\n";

		Vector3 dif = testvect4 - testvect3;
		cout << "(4,5,6) - (1,2,3) = " << dif << endl;

		cout << "Lets spawn a Camera [currently just a Vector3 position in space]:";
		m_sceneCamera = new Camera(Vector3(-200, 0, -30));

		std::cout << " " << m_sceneCamera << endl;

		m_testRasterizer = new Rasterizer(m_meshPool, m_screen);

		cout << "Initializing Main Scene.\n";
		m_mainScene.InitScene(m_sceneCamera);

		cout << "Main Scene Camera: " << m_mainScene.GetCamera() << endl;

		std::chrono::time_point<std::chrono::system_clock> start, end;
		start = std::chrono::system_clock::now();

		cout << "Loading OBJ Model File.\n";

		testOBJ->Load(TEST_MODEL_FILENAME);
		testOBJ2->Load("..\\DBG_GRID.obj");

		//VertexPool = testOBJ->ExtractVertexData(VERTEX_COUNT, MeshPool);
		m_meshPool = testOBJ->ExtractMeshData(m_vertexPool); //!>VertexPool is set up via reference
		m_meshPool2 = testOBJ2->ExtractMeshData(m_vertexPool);

		Mesh* grid = m_meshPool2.GetMesh("GRID");

		m_meshPool.AddMesh(grid);
		clock_t t;
		t = clock();

		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		cout << "Finished Loading OBJ Model File. Elapsed time is: " << elapsed_seconds.count() << endl;

		start = std::chrono::system_clock::now();

		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;

		cout << "Total rendered tri count is: " << EDGE_COUNT / 3 << " Render time: " << elapsed_seconds.count() << endl;

		SDL_Flip(m_screen);

		SDL_Delay(5000);
		SDL_FillRect(m_screen, nullptr, 0x000000);
		SDL_Flip(m_screen);

		cout << "Mesh[" << m_meshPool.GetMesh(0)->GetID().c_str() << "] World Coordinates: " << m_meshPool.GetMesh(0)->Location() << " Camera-Relative: " << WorldToCameraCoords(m_meshPool.GetMesh(0)->Location()) << endl;

		m_keystates = SDL_GetKeyState(nullptr);
		m_shouldQuit = false;

		cout << "Initializing Physics Manager\n";

		Core::Physics::SPBody* physCube = new Core::Physics::SPBody();
		physCube->SetMesh(*m_meshPool.GetMesh("DBG_CUBE"));
		physCube->SetMass(1.0f);
		physCube->SetAwakeState(false);

		Core::Physics::PhysicsManager::GetInstance().ConnectToEvent(Core::EventSys::EID_ENGINE_TICK_EVENT);
		Core::Physics::PhysicsManager::GetInstance().AddPhysObject(physCube);

		m_frame_delta = clock();
    }
    void EngineImpl::Run()
    {
		while (!m_shouldQuit)
		{
			m_frame_delta = (double)clock() - m_frame_delta;

			//std::cout << "[INFO] Previous frame took " << frame_delta / CLOCKS_PER_SEC << " ticks to render\n";

			SDL_PollEvent(&m_event);
			if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_ESCAPE)
				m_shouldQuit = true;

			if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_HOME)
			{
				bool state = Core::Physics::PhysicsManager::GetInstance().GetPhysObject(0)->GetAwakeState();
				Core::Physics::PhysicsManager::GetInstance().GetPhysObject(0)->SetAwakeState(!state);
			}

			if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_w)
			{
				m_mainScene.GetCamera()->Move(Vector3(0, 0, CAM_SPEED) * m_frame_delta);
			}
			if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_s)
				m_mainScene.GetCamera()->Move(Vector3(0, 0, -CAM_SPEED) * m_frame_delta);
			if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_a)
				m_mainScene.GetCamera()->Move(Vector3(-CAM_SPEED, 0, 0) * m_frame_delta);
			if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_d)
				m_mainScene.GetCamera()->Move(Vector3(CAM_SPEED, 0, 0) * m_frame_delta);
			if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_UP)
				m_mainScene.GetCamera()->Move(Vector3(0, CAM_SPEED, 0) * m_frame_delta);
			if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_DOWN)
			{
				m_mainScene.GetCamera()->Move(Vector3(0, -CAM_SPEED, 0) * m_frame_delta);
				m_evTest->FireEvent(m_eventID);
			}

			m_meshPool.GetMesh("DBG_CUBE")->Rotate(Vector3(0.0f, 0.5f, 0.0f) * m_frame_delta);

			Core::EventSys::EventManager::GetInstance().Update();

			m_meshPool.GetMesh("DBG_CUBE")->Draw();
			m_meshPool.GetMesh("DBG_GRID")->Draw();
			m_dbgServer.LogInfo("THIS IS A TEST MESSAGE\n");
			//testRasterizer->RasterizeScene();
			for (int i = 0; i < m_meshPool.length(); ++i)
			{
				m_meshPool.GetMesh(i)->Translate(Vector3(0.0f, 0.0f, 0.0f) /** frame_delta*/);
				//dbg_screen = TTF_RenderText_Solid(dbg_font, "FRAME TICK\n", color);
			}

			SDL_Flip(m_screen);
			//SDL_Delay(ENGINE_TICK);
			SDL_FillRect(m_screen, nullptr, 0x000000);

			char eventData[50] = "";
			memcpy(eventData, &m_frame_delta, sizeof(double));

			Core::EventSys::EventManager::GetInstance().FireEvent(Core::EventSys::EID_ENGINE_TICK_EVENT, eventData);
		}
    }
    int EngineImpl::Shutdown()
    {
		// emptying geometry pools

		std::cout << "Destroying Camera.\n";
		delete m_sceneCamera;
		m_sceneCamera = nullptr;

		std::cout << "Emptying Vertex Pool.\n";
		m_vertexPool.clear();

		std::cout << "Emptying Edge Pool.\n";
		m_edgePool.clear();

		std::cout << "Emptying Triangle Pool.";
		m_trianglePool.clear();

		getchar();

		SDL_Quit();

		return 0;
    }
} // Core

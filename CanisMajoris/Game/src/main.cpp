#include<iostream>
#include<SDL.h>
#include<SDL_draw.h>
#include<SDL_ttf.h>

//For debug purposes only!
#include<chrono>
#include<time.h>

//#include<boost/interprocess/windows_shared_memory.hpp>
//#include<boost/interprocess/mapped_region.hpp>

#include<Renderer/CoreUtils/Primitives/Vertex.h>

#include<Renderer/CoreUtils/Rasterizer/Rasterizer.h>
#include<Renderer/CoreUtils/Camera.h>
#include<Renderer/CoreUtils/Scene.h>

#include<FileIO/OBJImpex/Reader/IO_OBJLoader.h>
#include<Utils/Math/ConverterUtils.inl>
#include<Utils/Constants.h>
#include<Utils/Math/Vector2.h>

#include<Events/EventManager.h>
#include<Events/EventClient.h>
#include<Events/TestEventClient.h>

#include<Entities/Object.h>

#include <Physics/SimplePhysBody.h>
#include<Physics/PhysicsManager.h>

#include<Editor/ProcyonServer/EditorServer.h>
#include<Editor/ProcyonServer/ProcyonConstants.h>
#include <Entities/UIObject.h>
#include <Init/FontLoader.h>
#include <Init/InitStatusIndicator.h>

//#include<ScriptEngine.h>

int main(int argc, char* argv[])
{
	
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	TTF_Font *dbg_font = nullptr;
	dbg_font = TTF_OpenFont("ARLRDBD.TTF", 20);

	SDL_Surface* dbg_screen = nullptr;
	SDL_Color color = { 255, 255, 255 };
	//dbg_screen = TTF_RenderText_Solid(dbg_font, "Canis Majoris On-Screen Debug Text", color);

	//TTF_RenderText_Solid
	SDL_putenv("SDL_VIDEO_WINDOW_POS=center");
	SDL_Surface* screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("CANIS MAJORIS 3D PERSPECTIVE", nullptr);

	using namespace std;
	using namespace Core::Renderer::CoreUtils;
	using namespace Core::IO;
	using namespace boost::interprocess;

	cout << "Lets spawn a Camera [currently just a Vector3 position in space]:";
	Camera *SceneCamera = new Camera(Vector3(-200.0f, 95.0f, -1000.0f));

	cout << "Lets create our Scene.\n";
	Scene MainScene = Scene::GetInstance();
	cout << "Initializing Main Scene.\n";
	MainScene.InitScene(SceneCamera);

	Core::Init::FontLoader fontLoader;

	Core::Init::StatusIndicator::GetInstance().DisplayProgressSpinner();
	EventClientTest *evTest = new EventClientTest();
	EventClientTest *evReceiver = new EventClientTest();
	Core::EventSys::Event *testEvent = new Core::EventSys::Event();

	testEvent->eventType = 666;
	int eventID = -10;
	evTest->RegisterEvent(testEvent, eventID);
	cout << "evTest ID: " << evTest->clientID() << '\n';
	std::cout << "Event ID is: " << eventID << '\n';
	evReceiver->ConnectToEvent(eventID);
	cout << "receiver ID: " << evReceiver->clientID() << '\n';
	/*windows_shared_memory shm(create_only, "DBG_LOG_MEM", read_write, 1000);

	mapped_region region(shm, read_write);
	std::memset(region.get_address(), 'X', region.get_size());*/

	Core::Init::StatusIndicator::GetInstance().DisplayProgressSpinner();
	Editor::ProcyonServer dbgServer = Editor::ProcyonServer::GetInstance();

	cout << "Lets build a ModelFile and load our test model.\n";
	ModelFile* testOBJ = new ModelFile();
	ModelFile* testOBJ2 = new ModelFile();
	ModelFile* alphabet = new ModelFile();
	//testOBJ->ExtractVertexData();
	dbgServer.InitializeEditorServer();
	dbgServer.LogInfo("THIS IS A TEST MESSAGE\n");
	//dbgServer.LogInfo(SHARED_MEMORY_CLEAR);

	cout << "Lets test Vector2 in Polar and Cartesian systems.\n";
	using namespace Math;

	cout << " " << SceneCamera << endl;
	Core::Init::StatusIndicator::GetInstance().DisplayProgressSpinner();
	cout << "Lets create our Vertex Pool.\n";
	vector<Vertex*> VertexPool;
	vector<Vertex*> VertexPool2;
	vector<Vertex*> VertexPool3;
	
	cout << "Lets create our Edge Pool.\n";
	vector<Edge*> EdgePool;

	cout << "Lets create our Triangle Pool.\n";
	vector<Triangle*> TrianglePool;

	cout << "Lets create our Mesh Pool.\n";
	MeshContainer MeshPool;
	MeshContainer MeshPool2;
	MeshContainer MeshPool3;
	Rasterizer* testRasterizer = new Rasterizer(MeshPool, screen);

	cout << "Main Scene Camera: " << MainScene.GetCamera() << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	//ScriptEngine::Instance().LoadScript();

	//ScriptEngine::Instance().Execute();

	cout << "Loading OBJ Model File.\n";
	Core::Init::StatusIndicator::GetInstance().DisplayProgressSpinner();
	testOBJ->Load(TEST_MODEL_FILENAME);
	testOBJ2->Load("..\\10m_cube.obj");
	alphabet->Load("..\\alphabet.obj");

	//VertexPool = testOBJ->ExtractVertexData(VERTEX_COUNT, MeshPool);
	MeshPool = testOBJ->ExtractMeshData(VertexPool); //!>VertexPool is set up via reference
	MeshPool2 = testOBJ2->ExtractMeshData(VertexPool2);
	MeshPool3 = alphabet->ExtractMeshData(VertexPool3);

	Mesh* grid = MeshPool2.GetMesh("GRID");

	for (auto i = 0; i < MeshPool3.length(); ++i)
	{
		MeshPool.AddMesh(MeshPool3.GetMesh(i));
	}

	MeshPool.AddMesh(MeshPool2.GetMesh(1));
	MeshPool.AddMesh(grid);
	clock_t t;
	t = clock();

	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	cout << "Finished Loading OBJ Model File. Elapsed time is: " << elapsed_seconds.count() << endl;
	Core::Init::StatusIndicator::GetInstance().DisplayProgressSpinner();
	start = std::chrono::system_clock::now();

	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;

	cout << "Total rendered tri count is: " << EDGE_COUNT / 3 << " Render time: "<< elapsed_seconds.count() << endl;

	cout << "Mesh[" << MeshPool.GetMesh(0)->GetID().c_str() << "] World Coordinates: " << MeshPool.GetMesh(0)->Location() << " Camera-Relative: " << WorldToCameraCoords(MeshPool.GetMesh(0)->Location()) << endl;

	Uint8 *keystates = SDL_GetKeyState(nullptr);
	bool shouldQuit = false;
	SDL_Event event;
	Core::Init::StatusIndicator::GetInstance().DisplayProgressSpinner();
	cout << "Initializing Physics Manager\n";
	cout << MeshPool.GetMesh("DBG_CUBE")->Location() << endl;
	Core::Physics::SPBody *physCube = new Core::Physics::SPBody();
	physCube->SetMesh(*MeshPool.GetMesh("DBG_CUBE"));
	physCube->SetMass(1.0f);
	physCube->SetAwakeState(false);

	Core::Physics::PhysicsManager::GetInstance().ConnectToEvent(Core::EventSys::EID_ENGINE_TICK_EVENT);
	Core::Physics::PhysicsManager::GetInstance().AddPhysObject(physCube);

#pragma region comments
	//MeshPool.GetMesh("10M_CUBE")->SetLocation(Vector3(-2.6f, 384.0f, 505.0f));
	//Vector3 markerLocationReference = MeshPool.GetMesh("10M_CUBE")->GetVertices()[0]->Location();
	//calibration_marker->SetLocation(markerLocationReference);
	//calibration_marker2->SetLocation(Vector3(markerLocationReference.x, markerLocationReference.y + 50.0f, markerLocationReference.z));

	//std::cout << "MarkerLocationReference: " << markerLocationReference << endl;
	//std::cout << "Secondary Location: " << MeshPool.GetMesh("10M_CUBE")->GetVertices()[1]->Location() << endl;
	//std::cout << "10m in model-space = " << MeshPool.GetMesh("10M_CUBE")->GetVertices()[1]->Location() - markerLocationReference << endl;
#pragma endregion 

	cout << "Creating a new L3D Loader" << endl;

	//L3D_TEST newFileLoaderTest;

	cout << "Attempting to save test geometry to .L3D" << endl;

	//newFileLoaderTest.

	cout << "Operations performed successfully" << endl;

	double frame_delta = clock();
	Core::Init::StatusIndicator::GetInstance().DisplayProgressSpinner();
	Core::Game::Entities::Object test_object =  Core::Game::Entities::Object(MeshPool.GetMesh("DBG_CUBE"), Vector3(-100.0f, 50.0f, -200.0f));
	Core::Game::Entities::Object test_object2 = Core::Game::Entities::Object(MeshPool.GetMesh("Line02"), Vector3(-50.0f, 20.0f, -230.0f));
	Core::Game::Entities::UIObject uiTextTest = Core::Game::Entities::UIObject(MeshPool.GetMesh("f_a"), Vector3(100.0f, 100.0f, -200.0f));
	while (!shouldQuit)
	{
		frame_delta = (double)clock() - frame_delta;

		//std::cout << "[INFO] Previous frame took " << frame_delta / CLOCKS_PER_SEC << " ticks to render\n";

		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			shouldQuit = true;
		
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_HOME)
		{
			bool state = Core::Physics::PhysicsManager::GetInstance().GetPhysObject(0)->GetAwakeState();
			Core::Physics::PhysicsManager::GetInstance().GetPhysObject(0)->SetAwakeState(!state);
		}

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_w)
		{
			MainScene.GetCamera()->Move(Vector3(0, 0, CAM_SPEED) * frame_delta);
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
		{
			MainScene.GetCamera()->Move(Vector3(0, 0, -CAM_SPEED) * frame_delta);
			std:cout << MainScene.GetCamera()->Location() << std::endl;
		}
			
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a)
			MainScene.GetCamera()->Move(Vector3(-CAM_SPEED, 0, 0) * frame_delta);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d)
			MainScene.GetCamera()->Move(Vector3(CAM_SPEED, 0, 0) * frame_delta);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
			MainScene.GetCamera()->Move(Vector3(0, CAM_SPEED, 0) * frame_delta);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
		{
			MainScene.GetCamera()->Move(Vector3(0, -CAM_SPEED, 0) * frame_delta);
			evTest->FireEvent(eventID);
		}

		//MeshPool.GetMesh("DBG_CUBE")->Rotate(Vector3(0.0f, 0.5f, 0.0f) * frame_delta);
		//Vector3 cubeLoc = MeshPool.GetMesh("DBG_CUBE")->Location();

		test_object.Draw();
		
		//test_object.Translate(Vector3(0.0f, 0.0f, 0.0f));
		//test_object.Scale(0.5f);
		//test_object.Rotate(Vector3(0.0f, 0.5f, 1.0f));

		//test_object2.Rotate(Vector3(4.0f, 0.25f, 0.0f));

		test_object2.Draw();
		//test_object.Scale(1.2f);

		//uiTextTest.Rotate(Vector3(2.0f, 0.5f, 0.5f));
		uiTextTest.Draw();

		Core::EventSys::EventManager::GetInstance().Update();

		dbgServer.LogInfo("THIS IS A TEST MESSAGE\n");
		//testRasterizer->RasterizeScene(test_object.GetMesh());
		//for (int i = 0; i < MeshPool.length(); ++i)
		//{
		//	MeshPool.GetMesh(i)->Translate(Vector3(0.0f, 0.0f, 0.0f) /** frame_delta*/);
		//	//dbg_screen = TTF_RenderText_Solid(dbg_font, "FRAME TICK\n", color);
		//}

		SDL_Flip(screen);
		//SDL_Delay(ENGINE_TICK);
		SDL_FillRect(screen, nullptr, 0x000000);

		char eventData[50] = "";
		memcpy(eventData, &frame_delta, sizeof(double));

		Core::EventSys::EventManager::GetInstance().FireEvent(Core::EventSys::EID_ENGINE_TICK_EVENT, eventData);
	}

// emptying geometry pools

	cout << "Destroying Camera.\n";
	delete SceneCamera;
	SceneCamera = nullptr;

	cout << "Emptying Vertex Pool.\n";
	VertexPool.clear();

	cout << "Emptying Edge Pool.\n";
	EdgePool.clear();

	cout << "Emptying Triangle Pool.";
	TrianglePool.clear();

	getchar();

	SDL_Quit();

	return 0;
}
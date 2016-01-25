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

#include <Physics/SimplePhysBody.h>
#include<Physics/PhysicsManager.h>

#include<Editor/ProcyonServer/EditorServer.h>
#include<Editor/ProcyonServer/ProcyonConstants.h>

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

	SDL_Surface* screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("CANIS MAJORIS 3D PERSPECTIVE", nullptr);

	using namespace std;
	using namespace Core::Renderer::CoreUtils;
	using namespace Core::IO;
	using namespace boost::interprocess;

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
	Camera *SceneCamera = new Camera(Vector3(-200.0f, 95.0f, -200.0f));

	cout << " " << SceneCamera << endl;

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

	cout << "Lets create our Scene.\n";
	Scene MainScene = Scene::GetInstance();
	cout << "Initializing Main Scene.\n";
	MainScene.InitScene(SceneCamera);

	cout << "Main Scene Camera: " << MainScene.GetCamera() << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	//ScriptEngine::Instance().LoadScript();

	//ScriptEngine::Instance().Execute();

	cout << "Loading OBJ Model File.\n";
	
	testOBJ->Load(TEST_MODEL_FILENAME);
	testOBJ2->Load("..\\10m_cube.obj");
	alphabet->Load("..\\alphabet.obj");

	std::vector<Vertex*>   marker_vertices(6);
	std::vector<Edge*>     marker_edges;
	std::vector<Triangle*> marker_tris;
	marker_vertices[0] = new Vertex(-10.0f, -10.0f, 0.0f);
	marker_vertices[1] = new Vertex(  0.0f,   0.0f, 0.0f);
	marker_vertices[2] = new Vertex( 10.0f,  10.0f, 0.0f);
	marker_vertices[3] = new Vertex(-10.0f,  10.0f, 0.0f);
	marker_vertices[4] = new Vertex(  0.0f,   0.0f, 0.0f);
	marker_vertices[5] = new Vertex( 10.0f, -10.0f, 0.0f);

	marker_edges.push_back(new Edge(*marker_vertices[0], *marker_vertices[1]));
	marker_edges.push_back(new Edge(*marker_vertices[1], *marker_vertices[2]));
	marker_edges.push_back(new Edge(*marker_vertices[0], *marker_vertices[2]));
	
	marker_edges.push_back(new Edge(*marker_vertices[3], *marker_vertices[4]));
	marker_edges.push_back(new Edge(*marker_vertices[4], *marker_vertices[5]));
	marker_edges.push_back(new Edge(*marker_vertices[3], *marker_vertices[5]));

	marker_tris.push_back(new Triangle(*marker_edges.at(2), *marker_edges.at(1), *marker_edges.at(0)));
	marker_tris.push_back(new Triangle(*marker_edges.at(5), *marker_edges.at(4), *marker_edges.at(3)));

	Mesh* calibration_marker = new Mesh("f_calibration_marker", Scene::GetInstance().GetViewport(), marker_vertices, marker_edges, marker_tris);

	calibration_marker->InitPivot();

	Mesh* calibration_marker2 = calibration_marker;
	calibration_marker2->InitPivot();

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
	
	start = std::chrono::system_clock::now();

	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;

	cout << "Total rendered tri count is: " << EDGE_COUNT / 3 << " Render time: "<< elapsed_seconds.count() << endl;

	SDL_Flip(screen);

	SDL_Delay(5000);
	SDL_FillRect(screen, nullptr, 0x000000);
	SDL_Flip(screen);

	cout << "Mesh[" << MeshPool.GetMesh(0)->GetID().c_str() << "] World Coordinates: " << MeshPool.GetMesh(0)->Location() << " Camera-Relative: " << WorldToCameraCoords(MeshPool.GetMesh(0)->Location()) << endl;

	Uint8 *keystates = SDL_GetKeyState(nullptr);
	bool shouldQuit = false;
	SDL_Event event;

	cout << "Initializing Physics Manager\n";
	cout << MeshPool.GetMesh("10M_CUBE")->Location() << endl;
	Core::Physics::SPBody *physCube = new Core::Physics::SPBody();
	physCube->SetMesh(*MeshPool.GetMesh("DBG_CUBE"));
	physCube->SetMass(1.0f);
	physCube->SetAwakeState(false);

	Core::Physics::PhysicsManager::GetInstance().ConnectToEvent(Core::EventSys::EID_ENGINE_TICK_EVENT);
	Core::Physics::PhysicsManager::GetInstance().AddPhysObject(physCube);


	MeshPool.GetMesh("10M_CUBE")->SetLocation(Vector3(-2.6f, 384.0f, 505.0f));
	Vector3 markerLocationReference = MeshPool.GetMesh("10M_CUBE")->GetVertices()[0]->Location();
	calibration_marker->SetLocation(markerLocationReference);
	calibration_marker2->SetLocation(Vector3(markerLocationReference.x, markerLocationReference.y + 50.0f, markerLocationReference.z));

	std::cout << "MarkerLocationReference: " << markerLocationReference << endl;
	std::cout << "Secondary Location: " << MeshPool.GetMesh("10M_CUBE")->GetVertices()[1]->Location() << endl;
	std::cout << "10m in model-space = " << MeshPool.GetMesh("10M_CUBE")->GetVertices()[1]->Location() - markerLocationReference << endl;

	double frame_delta = clock();

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
			MainScene.GetCamera()->Move(Vector3(0, 0, -CAM_SPEED) * frame_delta);
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

		MeshPool.GetMesh("DBG_CUBE")->Rotate(Vector3(0.0f, 0.5f, 0.0f) * frame_delta);
		Vector3 cubeLoc = MeshPool.GetMesh("DBG_CUBE")->Location();


		MeshPool.GetMesh(18)->Rotate(Vector3(0.0f, 0.5f, 0.0f) * frame_delta);

		//MeshPool.GetMesh("y")->Rotate(Vector3(0.5f, 0.0f, 0.0f) * frame_delta);
		//MeshPool.GetMesh("y")->SetLocation(cubeLoc);
		//MeshPool.GetMesh("y")->Scale(2.0f * frame_delta);

		Core::EventSys::EventManager::GetInstance().Update();

		MeshPool.GetMesh("DBG_CUBE")->Draw();
		MeshPool.GetMesh("DBG_GRID")->Draw();
		MeshPool.GetMesh("a")->Draw();
		MeshPool.GetMesh("b")->Draw();
		MeshPool.GetMesh("c")->Draw();
		MeshPool.GetMesh("d")->Draw();
		MeshPool.GetMesh("e")->Draw();
		MeshPool.GetMesh("f")->Draw();
		MeshPool.GetMesh("0")->Draw();
		MeshPool.GetMesh("1")->Draw();
		MeshPool.GetMesh("2")->Draw();
		MeshPool.GetMesh("3")->Draw();
		MeshPool.GetMesh("4")->Draw();
		MeshPool.GetMesh("5")->Draw();
		MeshPool.GetMesh("6")->Draw();
		MeshPool.GetMesh("9")->Draw();
		MeshPool.GetMesh("8")->Draw();
		MeshPool.GetMesh("y")->Draw();
		for (int i = 0; i < MeshPool.length(); ++i)
		{
			MeshPool.GetMesh(i)->Draw();
		}
		MeshPool.GetMesh(20)->Rotate(Vector3(90.0f, 0.5f, 0.0f) * frame_delta);
		MeshPool.GetMesh(20)->Translate(Vector3(0.0f, 0.0f, 1.0f) * frame_delta);
		MeshPool.GetMesh(20)->Draw();

		calibration_marker->Draw();
		calibration_marker->Translate(Vector3(0.0f, 0.0f, 0.0f));
		calibration_marker2->Draw();
		calibration_marker2->Translate(Vector3(0.0f, 0.0f, 0.0f));
		/*for (int i = 0; i < MeshPool.length(); ++i)
		{
			if (MeshPool.GetMesh(i)->GetID() == "ROOT" ||
				MeshPool.GetMesh(i)->GetID() == "GRID")
			{
				continue;
			}

			MeshPool.GetMesh(i)->Draw();
		}*/
		dbgServer.LogInfo("THIS IS A TEST MESSAGE\n");
		//testRasterizer->RasterizeScene();
		for (int i = 0; i < MeshPool.length(); ++i)
		{
			MeshPool.GetMesh(i)->Translate(Vector3(0.0f, 0.0f, 0.0f) /** frame_delta*/);
			//dbg_screen = TTF_RenderText_Solid(dbg_font, "FRAME TICK\n", color);
		}

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
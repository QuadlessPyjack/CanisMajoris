#include<iostream>
#include<SDL.h>
#include<SDL_draw.h>
#include<SDL_ttf.h>

//For debug purposes only!
#include<chrono>

//#include<boost/interprocess/windows_shared_memory.hpp>
//#include<boost/interprocess/mapped_region.hpp>

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

#include<Editor/ProcyonServer/EditorServer.h>
#include<Editor/ProcyonServer/ProcyonConstants.h>

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
	SDL_WM_SetCaption("CANIS MAJORIS 3D PERSPECTIVE", NULL);

	using namespace std;
	using namespace Core::Renderer::CoreUtils;
	using namespace Core::IO;
	using namespace boost::interprocess;

	EventClientTest *evTest = new EventClientTest();
	Core::EventSys::EventManager::GetInstance().AddEvent(new Core::EventSys::Event());

	/*windows_shared_memory shm(create_only, "DBG_LOG_MEM", read_write, 1000);

	mapped_region region(shm, read_write);
	std::memset(region.get_address(), 'X', region.get_size());*/


	Editor::ProcyonServer dbgServer = Editor::ProcyonServer::GetInstance();

	cout << "Lets build a ModelFile and load our test model.\n";
	ModelFile* testOBJ = new ModelFile();
	ModelFile* testOBJ2 = new ModelFile();
	//testOBJ->ExtractVertexData();
	dbgServer.InitializeEditorServer();
	dbgServer.LogInfo("THIS IS A TEST MESSAGE\n");
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
	Camera *SceneCamera = new Camera(Vector3(-200, 0, -30));

	cout << " " << SceneCamera << endl;

	cout << "Lets create our Vertex Pool.\n";
	vector<Vertex*> VertexPool;
	
	cout << "Lets create our Edge Pool.\n";
	vector<Edge*> EdgePool;

	cout << "Lets create our Triangle Pool.\n";
	vector<Triangle*> TrianglePool;

	cout << "Lets create our Mesh Pool.\n";
	MeshContainer MeshPool;
	MeshContainer MeshPool2;
	Rasterizer* testRasterizer = new Rasterizer(MeshPool, screen);

	cout << "Lets create our Scene.\n";
	Scene MainScene = Scene::GetInstance();
	cout << "Initializing Main Scene.\n";
	MainScene.InitScene(SceneCamera);

	cout << "Main Scene Camera: " << MainScene.GetCamera() << endl;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	cout << "Loading OBJ Model File.\n";
	
	testOBJ->Load(TEST_MODEL_FILENAME);
	testOBJ2->Load("..\\DBG_GRID.obj");

	//VertexPool = testOBJ->ExtractVertexData(VERTEX_COUNT, MeshPool);
	MeshPool = testOBJ->ExtractMeshData(VertexPool); //!>VertexPool is set up via reference
	MeshPool2 = testOBJ2->ExtractMeshData(VertexPool);

	Mesh* grid = MeshPool2.GetMesh("GRID");

	MeshPool.AddMesh(grid);

	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	cout << "Finished Loading OBJ Model File. Elapsed time is: " << elapsed_seconds.count() << endl;
	
	start = std::chrono::system_clock::now();
	//Core::Renderer::CoreUtils::Mesh* testMesh = new Core::Renderer::CoreUtils::Mesh("TEST_MESH", screen, VertexPool, EdgePool, TrianglePool);
	//testMesh->Draw();
	//! Proudly DEPRECATED :D
	/*for (int i = 0; i < MeshPool.length(); i++)
	{
		MeshPool.GetMesh(i)->SetSurface(screen);
	}*/

	end = std::chrono::system_clock::now();
	elapsed_seconds = end - start;

	cout << "Total rendered tri count is: " << EDGE_COUNT / 3 << " Render time: "<< elapsed_seconds.count() << endl;

	SDL_Flip(screen);

	SDL_Delay(5000);
	SDL_FillRect(screen, NULL, 0x000000);
	SDL_Flip(screen);

	cout << "Mesh[" << MeshPool.GetMesh(0)->GetID().c_str() << "] World Coordinates: " << MeshPool.GetMesh(0)->Location() << " Camera-Relative: " << WorldToCameraCoords(MeshPool.GetMesh(0)->Location()) << endl;

	Uint8 *keystates = SDL_GetKeyState(NULL);
	bool shouldQuit = false;
	SDL_Event event;

	/*for (int i = 0; i < MeshPool.length(); ++i)
	{
		MeshPool.GetMesh(i)->Rotate(Vector3(0.0f, 0.0f, 0.0f), Vector3(400.0f, 0.0f, 0.0f));
	}*/

	while (!shouldQuit)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			shouldQuit = true;
		
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_w)
		{
			Vector3 aux = Vector3(0, 0, CAM_SPEED);
			MainScene.GetCamera()->Move(aux);
			//std::cout << "W KEY FIRED!\n";
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
			MainScene.GetCamera()->Move(Vector3(0, 0, -CAM_SPEED));
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a)
			MainScene.GetCamera()->Move(Vector3(-CAM_SPEED, 0, 0));
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_d)
			MainScene.GetCamera()->Move(Vector3(CAM_SPEED, 0, 0));
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
			MainScene.GetCamera()->Move(Vector3(0, CAM_SPEED, 0));
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
			MainScene.GetCamera()->Move(Vector3(0, -CAM_SPEED, 0));

		//
		MeshPool.GetMesh("DBG_CUBE")->Rotate(Vector3(0.0f, 0.5f, 0.0f));


		MeshPool.GetMesh("DBG_CUBE")->Draw();
		MeshPool.GetMesh("DBG_GRID")->Draw();
		dbgServer.LogInfo("THIS IS A TEST MESSAGE\n");
		//testRasterizer->RasterizeScene();
		for (int i = 0; i < MeshPool.length(); ++i)
		{
			MeshPool.GetMesh(i)->Translate(Vector3(0.0f, 0.0f, 0.0f));
			//MeshPool.GetMesh("DBG_CUBE")->Draw();
			//dbg_screen = TTF_RenderText_Solid(dbg_font, "FRAME TICK\n", color);
		}
		//int rVal = 100;
		//rVal = SDL_BlitSurface(dbg_screen, NULL, screen, NULL);
		SDL_Flip(screen);
		SDL_Delay(ENGINE_TICK);
		SDL_FillRect(screen, NULL, 0x000000);
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
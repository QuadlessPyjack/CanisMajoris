#include "boilerplate.h"

#include <fstream>

#include <FileIO/OBJImpex/Reader/IO_OBJLoader.h>
#include <Utils/MeshContainer.h>

#pragma comment(lib,"SDL.lib")
#pragma comment(lib,"SDLmain.lib") 

int main(int argc, char *argv[])
{
	using namespace std;
	if (argc <= 1 || argc > 4)
	{
		cout << ABOUT;
		return 0;
	}

	if (!strcmp(argv[2], SUPPORTED_FLAGS.CS_OUTPUT) && 
	    !strcmp(argv[2], SUPPORTED_FLAGS.H_OUTPUT)  &&
	    !strcmp(argv[2], SUPPORTED_FLAGS.LOG)
	   )
	{
		cout << INVALID_PARAM_MESSAGE + string("{0} \n", argv[2]);
		return -1;
	}

	Core::IO::ModelFile *model = new Core::IO::ModelFile();
	model->Load(argv[1]);

	char* endOfFileName = strstr(argv[1], ".");
	char dumpFileName[12];
	if (endOfFileName)
	{
		char *index = argv[1];
		int counter = 0;
		while (index != endOfFileName)
		{
			if (counter >= 12) break;
			dumpFileName[counter] = *index;
			index++;
			counter++;
		}
	}
	
	ofstream *dumpFile = new ofstream(dumpFileName, ofstream::out);

	std::vector<Core::Renderer::CoreUtils::Vertex*> vertexContainer;
	MeshContainer meshes(model->ExtractMeshData(vertexContainer));
	for (int index = 0; index < meshes.length(); ++index)
	{
		cout << meshes.GetMesh(index)->GetID() << endl;
		const string meshName = meshes.GetMesh(index)->GetID();
		if (strstr(meshName.c_str, "BN_"))
		{
			cout << meshes.GetMesh(index)->GetID() << endl;
		}
	}

	return 0;
}
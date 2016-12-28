#ifndef L3D_TEST_H
#define L3D_TEST_H
#include <FileIO/Lupus3DImpex/FileInfo.h>
#include <FileIO/Lupus3DImpex/IO_L3D.h>

class L3D_TEST
{
public:
	L3D_TEST();
	~L3D_TEST();

	bool SaveFileTest();
	bool LoadFileTest();

private:
	Core::IO::L3D::MeshFile m_testMesh;
	Core::IO::L3D::ModelCLR m_l3DLoader;
	string L3D_FILE_NAME = "test_model.l3d";
};



#endif
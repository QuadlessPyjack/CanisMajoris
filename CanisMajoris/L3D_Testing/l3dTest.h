#ifndef L3D_TEST_H
#define L3D_TEST_H
#include <Lupus3DImpex/FileInfo.h>
#include <Lupus3DImpex/IO_L3D.h>

class L3D_TEST
{
public:
	L3D_TEST();
	~L3D_TEST();

	bool SaveFileTest();
	bool LoadFileTest();
	bool BlankFileTest();

	bool VertexSaveTest();

private:
	Lupus3D::FileInfo::MeshFile m_testMesh;
	Lupus3D::Model m_l3DLoader;
	string L3D_FILE_NAME = "test_model.l3d";
};



#endif
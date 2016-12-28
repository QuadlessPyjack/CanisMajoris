#include "l3dTest.h"
#include <array>

namespace 
{
	Lupus3D::FileInfo::Vector3File CreateVector3File(float x, float y, float z)
	{
		Lupus3D::FileInfo::Vector3File v3;
		v3.x = x;
		v3.y = y;
		v3.z = z;

		return v3;
	}
 
	using namespace Lupus3D::FileInfo;

	const string MESH_NAME = "TEST_MESH_1";
	VertexFile vx1;
	VertexFile vx2;
	VertexFile vx3;

	EdgeFile e1;
	EdgeFile e2;
	EdgeFile e3;

	TriangleFile t1;
}


L3D_TEST::L3D_TEST()
{
	vx1.m_id = 0;
	vx1.m_meshOwnerName = MESH_NAME;
	vx1.m_dirtyFlag = false;
	vx1.m_v3 = CreateVector3File(0.0f, 1.2f, 3.4f);
	vx1.m_wsTransform = CreateVector3File(0.4f, 4.2f, 4.4f);

	vx2.m_id = 1;
	vx2.m_meshOwnerName = MESH_NAME;
	vx2.m_dirtyFlag = false;
	vx2.m_v3 = CreateVector3File(5.6f, 3.2f, 2.1f);
	vx2.m_wsTransform = CreateVector3File(45.4f, 3.2f, 6.4f);

	vx3.m_id = 2;
	vx3.m_meshOwnerName = MESH_NAME;
	vx3.m_dirtyFlag = false;
	vx3.m_v3 = CreateVector3File(-0.6f, -9.2f, 21.0f);
	vx3.m_wsTransform = CreateVector3File(-5.4f, -3.2f, -6.4f);

	e1.m_vertexIDs[0] = vx1.m_id;
	e1.m_vertexIDs[1] = vx1.m_id;
	e1.m_index = 0;
	e1.m_ownerTriangleIDs[0] = 4343;
	e1.m_ownerTriangleIDs[1] = 0;

	e1.m_vertexIDs[0] = vx2.m_id;
	e1.m_vertexIDs[1] = vx3.m_id;
	e1.m_index = 1;
	e1.m_ownerTriangleIDs[0] = 4343;
	e1.m_ownerTriangleIDs[1] = 0;

	e1.m_vertexIDs[0] = vx3.m_id;
	e1.m_vertexIDs[1] = vx1.m_id;
	e1.m_index = 2;
	e1.m_ownerTriangleIDs[0] = 4343;
	e1.m_ownerTriangleIDs[1] = 0;

	t1.m_id = 4343;
	t1.m_edgeIDs[0] = e1.m_index;
	t1.m_edgeIDs[1] = e2.m_index;
	t1.m_edgeIDs[2] = e3.m_index;

	m_testMesh.params.m_colour = CreateVector3File(0.0f, 255.0f, 255.0f);
	m_testMesh.params.m_dirtyFlag = false;
	
	m_testMesh.data.m_localEdges = vector<EdgeFile>(3);
	m_testMesh.data.m_localEdges[0] = e1;
	m_testMesh.data.m_localEdges[1] = e2;
	m_testMesh.data.m_localEdges[2] = e3;

	m_testMesh.data.m_localTris = vector<TriangleFile>(1, t1);

	m_testMesh.data.m_localVerts = vector<VertexFile>(3);
	m_testMesh.data.m_localVerts[0] = vx1;
	m_testMesh.data.m_localVerts[1] = vx2;
	m_testMesh.data.m_localVerts[2] = vx3;

	m_testMesh.params.m_pivot = CreateVector3File(0.0f, 0.0f, 5.0f);
	m_testMesh.params.m_wsRotation = CreateVector3File(0.0f, 0.0f, 5.0f);
	m_testMesh.params.m_scaleFactor = 1.0f;
	m_testMesh.params.meshID = MESH_NAME;
}

L3D_TEST::~L3D_TEST()
{

}

bool L3D_TEST::SaveFileTest()
{
	m_l3DLoader.AddMeshFile(m_testMesh);
	m_l3DLoader.Save(L3D_FILE_NAME);
	return true;
}

bool L3D_TEST::LoadFileTest()
{
	return true;
}

bool L3D_TEST::BlankFileTest()
{
	m_l3DLoader.CreateBlankFile(L3D_FILE_NAME);

	return true;
}

bool L3D_TEST::VertexSaveTest()
{
	return true;
}

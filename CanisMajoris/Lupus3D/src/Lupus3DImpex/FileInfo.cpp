#define L3D_LIB_COMPILE

#include <Lupus3DImpex/FileInfo.h>
#include <string>

using namespace std;

namespace Lupus3D  {
namespace FileInfo {

	char L3DFILE::SIGNATURE_BLOCK[9] = { 0 };
	uchar L3DFILE::VERTEX_BLOCK_SIZE[2] = { 0 };
	uchar L3DFILE::EDGE_BLOCK_SIZE[2] = { 0 };
	uchar L3DFILE::MESH_CONTAINER_SIZE[1] = { 0 };
	uchar L3DFILE::DESCRIPTOR_BLOCK_SIZE =  sizeof(FileInfo::L3DFILE::SIGNATURE_BLOCK) 
											+ sizeof(FileInfo::L3DFILE::VERTEX_BLOCK_SIZE) 
											+ sizeof(FileInfo::L3DFILE::EDGE_BLOCK_SIZE);

	MeshParamsFile::MeshParamsFile()
	: m_triCount(1)
	, m_vertCount(1)
	, m_scaleFactor(1.0f)
	, m_pivot(Vector3File())
	, m_colour(Vector3File())
	, m_boundingBox(Vector3File(), Vector3File())
	, m_dirtyFlag(true)
	{
	}

	MeshDataFile::MeshDataFile()
	: m_localVerts()
	, m_localEdges()
	, m_localTris()
	{	
	}

	Vector3File::Vector3File()
	: x(0.0f)
	, y(0.0f)
	, z(0.0f)
	{
	}

	BoundsFile::BoundsFile()
	: minCorner()
	, maxCorner()
	{}

	BoundsFile::BoundsFile(Vector3File min, Vector3File max) 
	:minCorner(min)
	,maxCorner(max)
	{}

	VertexFile::VertexFile()
	: m_id(0)
	, m_dirtyFlag(false)
	, m_meshOwnerName("NULL")
	, m_v3()
	, m_wsTransform()
	{
	}


} // namespace FileInfo
} // namespace Lupus3D
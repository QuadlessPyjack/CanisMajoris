#include <FileIO/Lupus3DImpex/FileInfo.h>

#include<string>

using namespace std;

namespace Core {
namespace IO   {
namespace L3D  {

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


} // namespace L3D
} // namespace IO
} // namespace Core
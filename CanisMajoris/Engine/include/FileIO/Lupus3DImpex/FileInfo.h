/////////////////////////////////////////////////// 
//! \brief   Validator Utils - Canis Majoris Renderer
//!	\author  Bogdan Vitel
//! \details Misc engine utility functions
//! \date    10/02/2015
//! \todo 
//////////////////////////////////////////
#ifndef L3D_FILEINFO_H
#define L3D_FILEINFO_H

#include<string>

using namespace std;

namespace Core {
namespace IO   {
namespace L3D  {

	class Vector3File
	{
	public:
		Vector3File();

		float x;
		float y;
		float z;
	};

	struct BoundsFile
	{
	public:
		BoundsFile();
		BoundsFile(Vector3File min, Vector3File max);

		Vector3File minCorner;
		Vector3File maxCorner;
	};

	class VertexFile
	{
	public:
		VertexFile();

		int m_id;
		bool m_dirtyFlag;

		string m_meshOwnerName;
		Vector3File m_v3;
		Vector3File m_wsTransform;
	};

	//class MeshFile;
	class EdgeFile
	{
	public:
		int m_ownerTriangleIDs[2];
		int m_index;
		string m_mesh_ownerRef;
		VertexFile m_startVert;
		VertexFile m_endVert;
	};

	class TriangleFile
	{
	public:
		int m_id;
		EdgeFile m_edgeA;
		EdgeFile m_edgeB;
		EdgeFile m_edgeC;
	};


	class MeshFile
	{
	public: 
		string meshID;
		VertexFile m_localVerts[10000];
		EdgeFile m_localEdges[10000];
		TriangleFile m_localTris[10000];

		int m_triCount;
		int m_vertCount;
		float m_scaleFactor;
		Vector3File m_wsRotation;
		Vector3File m_wsPivot;
		Vector3File m_pivot;
		Vector3File m_colour;
		BoundsFile m_boundingBox;

		bool m_dirtyFlag;
	};

} // namespace L3D
} // namespace IO
} // namespace Core

#endif // L3D_FILEINFO_H
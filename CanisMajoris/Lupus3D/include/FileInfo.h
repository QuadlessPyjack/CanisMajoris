/////////////////////////////////////////////////// 
//! \brief   Validator Utils - Canis Majoris Renderer
//!	\author  Bogdan Vitel
//! \details Misc engine utility functions
//! \date    10/02/2015
//! \todo 
//////////////////////////////////////////
#ifndef L3D_FILEINFO_H
#define L3D_FILEINFO_H

#ifdef L3D_LIB_COMPILE
#define L3D_LIB __declspec(dllexport)
#else
#define L3D_LIB __declspec(dllimport)
#endif

#include<string>
#include <vector>

using namespace std;

namespace Lupus3D  {
	typedef unsigned char uchar;
namespace FileInfo {

	// File Structure
	//
	// [ Signature + ID/Version Block = 9 bytes                   IDB ]
	// [ Number of vertices in VXB    = 2 bytes                  NVXB ]
	// [ Number of edges in ECB       = 2 bytes                  NECB ]
	// [ Number of meshes in MCB      = 1 byte                   NMCB ]
	// [ Vertex Container Block = NVXB * sizeof(VertexFile) bytes VXB ]
	// [ Edge Container Block = NECB * sizeof(EdgeFile) bytes     ECB ]
	// [ Triangle Container Block = 2 + NECB - NVXB (1)           TRB ]
	// [ Mesh container block = NMCB * sizeof(MeshFile) bytes     MCB ]
	//
	// 
	// (1) - Euler's Formula: v - e + f = 2 (https://en.wikipedia.org/wiki/Planar_graph#Euler.27s_formula)

	const char FILE_VERSION[9] = "L3D-V0.2";
	struct L3D_LIB L3DFILE
	{
		static char   SIGNATURE_BLOCK[9];
		static uchar  VERTEX_BLOCK_SIZE[2];
		static uchar  EDGE_BLOCK_SIZE[2];
		static uchar  MESH_CONTAINER_SIZE[1];
		static uchar  DESCRIPTOR_BLOCK_SIZE;
		uchar* VERTEX_BLOCK = nullptr;
		uchar* EDGE_BLOCK = nullptr;
		uchar* TRIANGLE_BLOCK = nullptr;
		uchar* MESH_BLOCK = nullptr;
	};

	class L3D_LIB Vector3File
	{
	public:
		Vector3File();

		float x;
		float y;
		float z;
	};

	struct L3D_LIB BoundsFile
	{
		BoundsFile();
		BoundsFile(Vector3File min, Vector3File max);

		Vector3File minCorner;
		Vector3File maxCorner;
	};

	class L3D_LIB VertexFile
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
	class L3D_LIB EdgeFile
	{
	public:
		int m_ownerTriangleIDs[2];
		int m_vertexIDs[2];
		int m_index;
		string m_mesh_ownerRef;
	};

	class L3D_LIB TriangleFile
	{
	public:
		int m_id;
		int m_edgeIDs[3];
		string m_mesh_ownerRef;
	};


	class L3D_LIB MeshParamsFile
	{
	public: 
		MeshParamsFile();

		string meshID;

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

	struct L3D_LIB MeshDataFile
	{
		MeshDataFile(string meshID);

		string m_meshID;

		vector<VertexFile> m_localVerts;
		vector<EdgeFile> m_localEdges;
		vector<TriangleFile> m_localTris;
	};

	inline MeshDataFile::MeshDataFile(string meshID)
	: m_meshID(meshID)
	{
		vector<VertexFile>::iterator it_vx;
		vector<EdgeFile>::iterator it_edges;
		vector<TriangleFile>::iterator it_triangles;

		// Set up mesh ownership IDs on owned geometry

		for (it_vx = m_localVerts.begin(); it_vx != m_localVerts.end(); ++it_vx)
		{
			it_vx->m_meshOwnerName = m_meshID;
		}

		for (it_edges = m_localEdges.begin(); it_edges != m_localEdges.end(); ++it_edges)
		{
			it_edges->m_mesh_ownerRef = m_meshID;

			it_edges->m_index
		}

		for (it_triangles = m_localTris.begin(); it_triangles != m_localTris.end(); ++it_triangles)
		{
			it_triangles->m_mesh_ownerRef = m_meshID;
		}

		// Set up internal geometry cross-references

		for (it_edges = )
	}

	struct L3D_LIB MeshFile
	{
		MeshDataFile data;
		MeshParamsFile params;
	};

} // namespace FileInfo
} // namespace Lupus3D

#endif // L3D_FILEINFO_H
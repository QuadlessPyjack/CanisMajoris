////////////////////////////////////////// 
//! \brief   IO_L3D - Canis Majoris Renderer
//! \author	 Bogdan Vitel
//! \details L3D File Loader src
//!          Ditched C# implementation in favour of full native solution
//! \date	 Created: 25/04/2016 Rewrite: 24/07/2016
//! \todo Create unified load method wrapper for Vertex, Edge and Triangle data
//!	\todo Read Mesh Object names and register them in vertices, also spawn shell mesh objects
//////////////////////////////////////////

#define L3D_LIB_COMPILE

// File Structure
//
// [ Signature + ID/Version Block = 8 bytes                   IDB ]
// [ Number of vertices in VXB    = 2 bytes                  NVXB ]
// [ Number of edges in ECB       = 2 bytes                  NECB ]
// [ Number of meshes in MCB      = 1 byte                   NMCB ]
// [ Vertex container Block = NVXB * sizeof(VertexFile) bytes VXB ]
// [ Edge Container Block = NECB * sizeof(EdgeFile) bytes     ECB ]
// [ Triangle Container Block = 2 + NECB - NVXB (1)           TRB ]
// [ Mesh container block = NMCB * sizeof(MeshFile) bytes     MCB ]
//
// 
// (1) - Euler's Formula: v - e + f = 2 (https://en.wikipedia.org/wiki/Planar_graph#Euler.27s_formula)



#include <IO_L3D.h>
#include <validation/Validators.inl>
#include <iostream>
#include <list>

namespace
{
	int ConvertASCIIArrayToInt(char* input)
	{
		int inputSize = 0;

		for (int i = 0; i < strlen(input); ++i)
		{
			inputSize *= 10;
			inputSize += input[i];
		}

		return inputSize;
	}

	int ConvertASCIIArrayToInt(unsigned char* input)
	{
		int inputSize = 0;

		for (int i = 0; i < strlen((char*)input); ++i)
		{
			inputSize *= 10;
			inputSize += input[i];
		}

		return inputSize;
	}
}

namespace Lupus3D  {

	Model::Model()
	{
	}

	Model::Model(std::string filePath)
	: m_meshes()
	{

	}

	void Model::AddMeshFile(FileInfo::MeshFile meshFile)
	{
		m_meshes.push_back(meshFile);
	}

	void Model::CreateBlankFile(string fileName)
	{
		createBlankFile(fileName);
		m_l3d_file.close();
	}

	void Model::Load(std::string filePath)
	{
		if (m_l3d_file)
		{
			if (m_l3d_file.is_open())
			{
				m_l3d_file.flush();
				m_l3d_file.close();
			}
		}

		m_l3d_file = fstream(filePath, ios::in | ios::binary);
		FileInfo::L3DFILE fileMap;
		FileInfo::MeshDataFile *content = nullptr;

		if (!loadDescriptor(fileMap))
		{
			return;
		}

		if (!loadNBlock(fileMap))
		{
			return;
		}

		if (!loadGeometryContent(fileMap, content))
		{
			return;
		}

		// TODO: Implement file read sequences
	}

	void Model::Save(std::string filePath)
	{
		if (m_meshes.size() == 0)
		{
			cout << "Nothing to save!" << endl;
			return;
		}

		int numberOfMeshes = m_meshes.size();
		FileInfo::MeshDataFile *contentData = new FileInfo::MeshDataFile[numberOfMeshes];
		FileInfo::MeshParamsFile *contentParams = new FileInfo::MeshParamsFile[numberOfMeshes];

		for (int index = 0; index < m_meshes.size(); ++index)
		{
			contentData[index] = m_meshes[index].data;
			contentParams[index] = m_meshes[index].params;
		}

		writeDescriptor(filePath);

		writeGeometryContent(contentData);

		writeMeshParameters(contentParams);

		contentData = nullptr;
		contentParams = nullptr;

		delete[]contentData;
		delete[]contentParams;
	}

	bool Model::IsValid()
	{
		return true;
	}

	void Model::createBlankFile(string fileName)
	{
		m_l3d_file = fstream(fileName, ios::out | ios::binary);
		FileInfo::MeshParamsFile blankMesh;
		FileInfo::MeshDataFile blankMeshData;
		blankMesh.meshID = "NOT_SO_NULL";
		blankMeshData.m_localVerts.assign(5, FileInfo::VertexFile());
		blankMeshData.m_localEdges.assign(4, FileInfo::EdgeFile());
		blankMeshData.m_localTris.assign(1, FileInfo::TriangleFile());

		FileInfo::L3DFILE fileMap;
		strcpy(fileMap.SIGNATURE_BLOCK, FileInfo::FILE_VERSION);
		int numberOfVertices = blankMeshData.m_localVerts.size();
		int numberOfEdges = blankMeshData.m_localEdges.size();
		int numberOfTriangles = 2 + numberOfEdges - numberOfVertices;

		int vertexBlockSize = sizeof(FileInfo::VertexFile) * numberOfVertices;
		int nvxb_length = sizeof(FileInfo::L3DFILE::VERTEX_BLOCK_SIZE);

		int edgeBlockSize = sizeof(FileInfo::EdgeFile) * numberOfEdges;
		int necb_length = sizeof(FileInfo::L3DFILE::EDGE_BLOCK_SIZE);

		int triangleBlockSize = sizeof(FileInfo::TriangleFile) * numberOfTriangles;

		// Check if the number of vertices that need storing can fit in 2 bytes (char[2] - VERTEX_BLOCK_SIZE)
		// We multiply the array length (sizeof char[2]) by UCHAR_MAX which holds the exact size of a char on this system (ie. 255).
		// This gives us the greatest number we can express/store within 2 bytes
		if (numberOfVertices < UCHAR_MAX * nvxb_length)
		{
			memcpy(fileMap.VERTEX_BLOCK_SIZE, &numberOfVertices, nvxb_length);
		}
		// The number of vertices is too high, truncate to 1 byte
		else
		{
			fileMap.VERTEX_BLOCK_SIZE[0] = UCHAR_MAX;
			nvxb_length = 1;
		}

		if (numberOfEdges < UCHAR_MAX * necb_length)
		{
			memcpy(fileMap.EDGE_BLOCK_SIZE, &numberOfEdges, necb_length);
		}
		else
		{
			fileMap.EDGE_BLOCK_SIZE[0] = UCHAR_MAX;
			necb_length = 1;
		}

		fileMap.VERTEX_BLOCK = (uchar*)&blankMeshData.m_localVerts[0];
		fileMap.EDGE_BLOCK = (uchar*)&blankMeshData.m_localEdges[0];
		fileMap.TRIANGLE_BLOCK = (uchar*)&blankMeshData.m_localTris[0];

		// Write signature and advance write pointer
		m_l3d_file.write(fileMap.SIGNATURE_BLOCK, strlen(fileMap.SIGNATURE_BLOCK));
		long pos = m_l3d_file.tellp();
		m_l3d_file.seekp(pos);
		// Write the int describing the size of the VXB and advance write pointer
		m_l3d_file.write((char*)fileMap.VERTEX_BLOCK_SIZE, nvxb_length);
		pos = m_l3d_file.tellp();
		m_l3d_file.seekp(pos);
		// Write the int describing the size of the ECB and advance write pointer
		m_l3d_file.write((char*)fileMap.EDGE_BLOCK_SIZE, necb_length);
		pos = m_l3d_file.tellp();
		m_l3d_file.seekp(pos);
		// Write the contents of the Vertex Container Array into the VXB and advance write pointer
		m_l3d_file.write((char*)fileMap.VERTEX_BLOCK, vertexBlockSize);
		pos = m_l3d_file.tellp();
		m_l3d_file.seekp(pos);
		// Write the contents of the Edge Container Array into the ECB and advance write pointer
		m_l3d_file.write((char*)fileMap.EDGE_BLOCK, edgeBlockSize);
		pos = m_l3d_file.tellp();
		m_l3d_file.seekp(pos);
		// Write the contents of the Triangle Container Array into the TRB and advance write pointer
		m_l3d_file.write((char*)fileMap.TRIANGLE_BLOCK, triangleBlockSize);
		pos = m_l3d_file.tellp();
		m_l3d_file.seekp(pos);


		std::cout << "VXB size: " << vertexBlockSize << std::endl;
		std::cout << "ECB size: " << edgeBlockSize << std::endl;
	}

	void Model::writeDescriptor(string fileName)
	{
		m_l3d_file = fstream(fileName, ios::out | ios::binary);
		FileInfo::L3DFILE fileMap;

		// Write signature and advance write pointer
		m_l3d_file.write(fileMap.SIGNATURE_BLOCK, strlen(fileMap.SIGNATURE_BLOCK));
		long pos = m_l3d_file.tellp();
		m_l3d_file.seekp(pos);
	}

	void Model::writeGeometryContent(FileInfo::MeshDataFile content[])
	{
		if (!m_l3d_file.is_open())
		{
			return;
		}

		if (!content)
		{
			return;
		}

		int vertexCount = 0, edgeCount = 0, trianglesCount = 0;

		int totalMeshes = sizeof(content) / sizeof(&content[0]);
		for (int index = 0; index < totalMeshes; ++index)
		{
			vertexCount += content[index].m_localVerts.size();
			edgeCount += content[index].m_localEdges.size();
		}

		trianglesCount = 2 + edgeCount - vertexCount;
		if (totalMeshes == 0)
		{
			return;
		}

		std::vector<FileInfo::VertexFile> vertices(content[0].m_localVerts);
		std::vector<FileInfo::EdgeFile> edges(content[0].m_localEdges);
		std::vector<FileInfo::TriangleFile> triangles(content[0].m_localTris);

		if (totalMeshes != 1)
		{
			for (int index = 1; index < totalMeshes; ++index)
			{
				int currentVXArraySize = vertices.size();
				int currentEArraySize = edges.size();
				int currentTArraySize = triangles.size();

				vertices.insert(vertices.begin() + vertices.size(), content[totalMeshes].m_localVerts.begin(), content[totalMeshes].m_localVerts.end());
				edges.insert(edges.begin() + edges.size(), content[totalMeshes].m_localEdges.begin(), content[totalMeshes].m_localEdges.end());
				triangles.insert(triangles.begin() + triangles.size(), content[totalMeshes].m_localTris.begin(), content[totalMeshes].m_localTris.end());
			}
		}

		FileInfo::L3DFILE m_fileMap;

		const int header_length = sizeof(FileInfo::L3DFILE::SIGNATURE_BLOCK);
		int nvxb_length = sizeof(FileInfo::L3DFILE::VERTEX_BLOCK_SIZE);
		int necb_length = sizeof(FileInfo::L3DFILE::EDGE_BLOCK_SIZE);
		int nmcb_length = sizeof(FileInfo::L3DFILE::MESH_CONTAINER_SIZE);

		int vertexBlockSize = sizeof(FileInfo::VertexFile) * vertexCount;
		int edgeBlockSize = sizeof(FileInfo::EdgeFile) * edgeCount;
		int triangleBlockSize = sizeof(FileInfo::TriangleFile) * trianglesCount;

		m_l3d_file.seekp(sizeof(FileInfo::L3DFILE::SIGNATURE_BLOCK));
		// Check if the number of vertices/edges that need storing can fit in 2 bytes (ie. char[2] - VERTEX_BLOCK_SIZE)
		// We multiply the array length (sizeof char[2]) by UCHAR_MAX which holds the exact size of a char on this system (ie. 255).
		// This gives us the greatest number we can express/store within 2 bytes
		setGeometryBlockSize(m_fileMap.VERTEX_BLOCK_SIZE, vertexCount, nvxb_length);

		setGeometryBlockSize(m_fileMap.EDGE_BLOCK_SIZE, edgeCount, necb_length);

		setGeometryBlockSize(m_fileMap.MESH_CONTAINER_SIZE, totalMeshes, nmcb_length);

		m_fileMap.VERTEX_BLOCK = (uchar*)&vertices[0];
		m_fileMap.EDGE_BLOCK = (uchar*)&edges[0];
		m_fileMap.TRIANGLE_BLOCK = (uchar*)&triangles[0];

		// Write the contents of the Vertex Container Array into the VXB and advance write pointer
		m_l3d_file.write((char*)m_fileMap.VERTEX_BLOCK, vertexBlockSize);
		long pos = m_l3d_file.tellp();
		m_l3d_file.seekp(pos);
		// Write the contents of the Edge Container Array into the ECB and advance write pointer
		m_l3d_file.write((char*)m_fileMap.EDGE_BLOCK, edgeBlockSize);
		pos = m_l3d_file.tellp();
		m_l3d_file.seekp(pos);
		// Write the contents of the Triangle Container Array into the TRB and advance write pointer
		m_l3d_file.write((char*)m_fileMap.TRIANGLE_BLOCK, triangleBlockSize);
		pos = m_l3d_file.tellp();
		m_l3d_file.seekp(pos);
	}

	void Model::writeMeshParameters(FileInfo::MeshParamsFile meshParams[])
	{
		if ((long)m_fileMap.VERTEX_BLOCK_SIZE < 0)
		{
			return;
		}

		if ((long)m_fileMap.EDGE_BLOCK_SIZE < 0)
		{
			return;
		}

		if (m_fileMap.TRIANGLE_BLOCK == nullptr)
		{
			return;
		}

		if (!m_l3d_file.is_open())
		{
			return;
		}

		long mesh_block_offset = (int)m_fileMap.VERTEX_BLOCK_SIZE + (int)m_fileMap.EDGE_BLOCK_SIZE + sizeof(m_fileMap.TRIANGLE_BLOCK);
		long mesh_block_size = sizeof(&meshParams[0]);

		m_l3d_file.write((char*)m_fileMap.MESH_BLOCK, mesh_block_size);

		long pos = m_l3d_file.tellp();
		m_l3d_file.seekp(pos);
	}

	void Model::setGeometryBlockSize(uchar fileBlockEntry[], int geometricObjectCount, int &block_length)
	{
		if (!fileBlockEntry)
		{
			return;
		}

		block_length = sizeof(fileBlockEntry);

		// Check if the number of vertices that need storing can fit in 2 bytes (char[2] - VERTEX_BLOCK_SIZE)
		// We multiply the array length (sizeof char[2]) by UCHAR_MAX which holds the exact size of a char on this system (ie. 255).
		// This gives us the greatest number we can express/store within 2 bytes
		if (geometricObjectCount < UCHAR_MAX * block_length)
		{
			memcpy(fileBlockEntry, &geometricObjectCount, block_length);
		}
		// The number of vertices is too high, truncate to 1 byte
		else
		{
			fileBlockEntry[0] = UCHAR_MAX;
			block_length = 1;
		}

		long pos = m_l3d_file.tellp();
		m_l3d_file.seekp(pos);

		m_l3d_file.write((char*)fileBlockEntry, block_length);
	}

	bool Model::loadDescriptor(FileInfo::L3DFILE &fileMap)
	{
		m_l3d_file.read(&fileMap.SIGNATURE_BLOCK[0], strlen(fileMap.SIGNATURE_BLOCK));
		long pos = m_l3d_file.tellg();
		m_l3d_file.seekg(pos);

		if (!fileMap.SIGNATURE_BLOCK)
		{
			return false;
		}

		if (strcmp(fileMap.SIGNATURE_BLOCK, FileInfo::FILE_VERSION) != 0)
		{
			std::cout << "Attempted to load file with an unsupported version number\n";
			return false;
		}

		return true;
	}

	bool Model::loadNBlock(FileInfo::L3DFILE &fileMap)
	{
		int nvxb_length = sizeof(FileInfo::L3DFILE::VERTEX_BLOCK_SIZE);
		int necb_length = sizeof(FileInfo::L3DFILE::EDGE_BLOCK_SIZE);
		int nmcb_length = sizeof(FileInfo::L3DFILE::MESH_CONTAINER_SIZE);

		m_l3d_file.read((char*)fileMap.VERTEX_BLOCK_SIZE, nvxb_length);
		long pos = m_l3d_file.tellg();
		m_l3d_file.seekg(pos);

		m_l3d_file.read((char*)fileMap.EDGE_BLOCK_SIZE, necb_length);
		pos = m_l3d_file.tellg();
		m_l3d_file.seekg(pos);

		m_l3d_file.read((char*)fileMap.MESH_CONTAINER_SIZE, nmcb_length);
		pos = m_l3d_file.tellg();
		m_l3d_file.seekg(pos);

		// Validate loaded data

		if (!IOValidateInt(fileMap.VERTEX_BLOCK_SIZE, 2))
		{
			return false;
		}

		if (!IOValidateInt(fileMap.EDGE_BLOCK_SIZE, 2))
		{
			return false;
		}

		if (!IOValidateInt(fileMap.MESH_CONTAINER_SIZE))
		{
			return false;
		}

		return true;
	}

	bool Model::loadGeometryContent(FileInfo::L3DFILE& fileMap, FileInfo::MeshDataFile content[])
	{
		int vxb_size = ConvertASCIIArrayToInt(fileMap.VERTEX_BLOCK_SIZE) * sizeof(FileInfo::VertexFile);
		int ecb_size = ConvertASCIIArrayToInt(fileMap.EDGE_BLOCK_SIZE) * sizeof(FileInfo::EdgeFile);
		int tcb_size = (2 + ecb_size - vxb_size) * sizeof(FileInfo::TriangleFile);
		int mcb_size = ConvertASCIIArrayToInt(fileMap.MESH_CONTAINER_SIZE) * sizeof(FileInfo::MeshParamsFile);

		m_l3d_file.read((char*)fileMap.VERTEX_BLOCK, vxb_size);
		
		if (!fileMap.VERTEX_BLOCK)
		{
			return false;
		}
		
		long pos = m_l3d_file.tellg();
		m_l3d_file.seekg(pos);

		m_l3d_file.read((char*)fileMap.EDGE_BLOCK, ecb_size);

		if (!fileMap.EDGE_BLOCK)
		{
			return false;
		}

		pos = m_l3d_file.tellg();
		m_l3d_file.seekg(pos);
		
		m_l3d_file.read((char*)fileMap.TRIANGLE_BLOCK, tcb_size);

		if (!fileMap.TRIANGLE_BLOCK)
		{
			return false;
		}

		pos = m_l3d_file.tellg();
		m_l3d_file.seekg(pos);

		m_l3d_file.read((char*)fileMap.MESH_BLOCK, mcb_size);

		if (!fileMap.MESH_BLOCK)
		{
			return false;
		}

		pos = m_l3d_file.tellg();
		m_l3d_file.seekg(pos);

		int meshDataCount = sizeof(fileMap.MESH_BLOCK) / sizeof(FileInfo::MeshParamsFile);
		int totalVertexCount = sizeof(fileMap.VERTEX_BLOCK) / sizeof(FileInfo::VertexFile);
		int totalEdgeCount = sizeof(fileMap.EDGE_BLOCK) / sizeof(FileInfo::EdgeFile);
		int totalTriangleCount = sizeof(fileMap.TRIANGLE_BLOCK) / sizeof(FileInfo::TriangleFile);

		content = new FileInfo::MeshDataFile[meshDataCount];

		std::vector<FileInfo::VertexFile> vertices(totalVertexCount);
		std::vector<FileInfo::EdgeFile> edges(totalEdgeCount);
		std::vector<FileInfo::TriangleFile> triangles(totalTriangleCount);
		
		char* pReader = (char*)&fileMap.VERTEX_BLOCK[0];
		int currentMeshIndex = 0;
		// ID of the current owner mesh
		string currentOwnerName = "";

		// Counts the geometric object index for the current owner mesh
		int currentVertexRelativeIndex = 0;
		int currentEdgeRelativeIndex = 0;
		int currentTriangleRelativeIndex = 0;

		for (int index = 0; index <	totalVertexCount; ++index)
		{
			FileInfo::VertexFile vertexFile;
			memcpy(&vertexFile, pReader, sizeof(FileInfo::VertexFile));

			vertices[index] = vertexFile;
			if (currentOwnerName != vertexFile.m_meshOwnerName)
			{
				// We have found a new owner mesh ID, update ID
				// advance mesh index and reset relative vertex index
				currentOwnerName = vertexFile.m_meshOwnerName;
				currentMeshIndex++;
				currentVertexRelativeIndex = 0;
			}
			
			content[currentMeshIndex].m_localVerts[currentVertexRelativeIndex] = vertexFile;

			// Advance vertex index relative to current mesh
			currentVertexRelativeIndex++;

			// Advance to memory location of next vertex file object
			pReader += sizeof(FileInfo::VertexFile);
		}

		currentOwnerName = "";
		pReader = (char*)&fileMap.EDGE_BLOCK[0];

		for (int index = 0; index < totalEdgeCount; ++index)
		{
			FileInfo::EdgeFile edgeFile;
			memcpy(&edgeFile, pReader, sizeof(FileInfo::EdgeFile));

			edges[index] = edgeFile;
			if (currentOwnerName != edgeFile.m_mesh_ownerRef)
			{
				// We have found a new owner mesh ID, update ID
				// advance mesh index and reset relative vertex index
				currentOwnerName = edgeFile.m_mesh_ownerRef;
				currentMeshIndex++;
				currentEdgeRelativeIndex = 0;
			}

			content[currentMeshIndex].m_localEdges[currentEdgeRelativeIndex] = edgeFile;

			// Advance vertex index relative to current mesh
			currentEdgeRelativeIndex++;

			// Advance to memory location of next vertex file object
			pReader += sizeof(FileInfo::EdgeFile);
		}

		currentOwnerName = "";
		pReader = (char*)&fileMap.TRIANGLE_BLOCK[0];

		for (int index = 0; index < totalTriangleCount; ++index)
		{
			FileInfo::TriangleFile triangleFile;
			memcpy(&triangleFile, pReader, sizeof(FileInfo::TriangleFile));

			triangles[index] = triangleFile;
			if (currentOwnerName != triangleFile.m_id)
			{
				// We have found a new owner mesh ID, update ID
				// advance mesh index and reset relative vertex index
				currentOwnerName = triangleFile.m_mesh_ownerRef;
				currentMeshIndex++;
				currentTriangleRelativeIndex = 0;
			}

			content[currentMeshIndex].m_localTris[currentTriangleRelativeIndex] = triangleFile;

			// Advance vertex index relative to current mesh
			currentTriangleRelativeIndex++;

			// Advance to memory location of next vertex file object
			pReader += sizeof(FileInfo::TriangleFile);
		}

		return true;
	}

	bool Model::loadMeshParameters(FileInfo::L3DFILE& fileMap)
	{
		return true;
	}

	//std::vector<FileInfo::MeshFile> GetMeshFiles()
	//{
	//	/*if (Model::IsValid())
	//	{

	//		return meshes;
	//	}*/

	//	return std::vector<FileInfo::MeshFile>(0);
	//}

} // namespace Lupus3D
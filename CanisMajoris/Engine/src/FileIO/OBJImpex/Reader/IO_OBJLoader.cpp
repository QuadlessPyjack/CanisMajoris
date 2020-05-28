////////////////////////////////////////// 
//! \brief   IO_OBJLoader - Canis Majoris Renderer
//! \author	 Bogdan Vitel
//! \details OBJ File Loader src
//! \date	 10/11/2014
//! \todo Create unified load method wrapper for Vertex, Edge and Triangle data
//!	\todo Read Mesh Object names and register them in vertices, also spawn shell mesh objects
//////////////////////////////////////////

#include<sstream>
#include<string>
#include<filesystem>
//For debug purposes only. Remove when done
#include<iostream>

#include <FileIO\OBJImpex\Reader\IO_OBJLoader.h>
#include <Utils\Constants.h>

namespace Core {
namespace IO   {
 ModelFile::ModelFile()
 {};
 
 void ModelFile::Load(const std::string filePath)
 {
  m_input = new std::ifstream(filePath);
  m_filename = filePath;
 	
  if (std::filesystem::file_size(filePath) == 0)
   std::cout << "[OBJ LOAD DBG] Incorrect Path or Missing File Error! (" << filePath << ")\n";
  else
   ;
   //m_input->open(filePath);
 };
 
 void ModelFile::Save(std::string filePath)
 {};
 
 std::vector<Renderer::CoreUtils::Vertex*> ModelFile::ExtractVertexData(int& vertCount, MeshContainer& MeshData)
 {
  std::vector<Renderer::CoreUtils::Vertex*> VertexData;
  std::string line;

  if (m_input && *m_input)
  {
   //std::cout << "FILE DUMP: " << m_input->rdbuf()<<'\n';
   std::string owningMesh = "ROOT";
   int meshIndex = 0;
 
   while (!m_input->eof())
   {
 	if (!std::getline(*m_input, line))
 	{
 	 std::cout << "END_OF_FILE" << std::endl;
 	}
 	else
 	{
 	 if (line[0] == 'v')
 	 {
 	  std::string raw_value;
 	  std::stringstream line2(line);
 	  while (line2 >> raw_value)
 	  {
 	   if (raw_value.compare("v") != 0)
 	   {
 		//! \todo if it degrades performance too much on higher vert counts, consider relying on the header, ignore the guy below
 		vertCount++; //!< We could've just stripped the vert count right from the header but its safer this way
 		float raw_coordinates[3];
 		raw_coordinates[0] = stof(raw_value) * AMPLIFICATION_FACTOR + TEMP_OFFSETX;
 		line2 >> raw_value;
 		raw_coordinates[1] = stof(raw_value) * AMPLIFICATION_FACTOR + TEMP_OFFSETY;
 		line2 >> raw_value;
 		raw_coordinates[2] = stof(raw_value);
 
 		VertexData.push_back(new Renderer::CoreUtils::Vertex(raw_coordinates));
 		VertexData.back()->SetOwner(owningMesh);
 	   }	
  } // while (line2 >> raw_value)
  } // if (line[0] == 'v')
  } // if (!std::getline(*m_input, line)) else
  } // while not eof
  } // while input buffer

 m_input->close();
 return VertexData;
 };
 
 std::vector<Renderer::CoreUtils::Edge*> ModelFile::ExtractEdgeData(int& edgeCount, std::vector<Renderer::CoreUtils::Vertex*>& vertexPoolRef)
 {
  std::vector<Renderer::CoreUtils::Edge*> EdgeData;
  std::string line;
 
  m_input->open(m_filename);
  std::cout << "OBJ FILE REOPENED\n";
  if (m_input && *m_input)
  {
   // std::cout << "FILE DUMP: " << m_input->rdbuf()<<'\n';
   while (!m_input->eof())
   {
 	if (!getline(*m_input, line))
 	{
 	 std::cout << "END_OF_FILE" << std::endl;
 	}
 	else
 	{
 	 if (line[0] == 'f')
 	{
 	std::string raw_value;
 	std::stringstream line2(line);
 	while (line2 >> raw_value)
 	{
 	 if (raw_value.compare("f") != 0)
 	 {
      //! \todo if it degrades performance too much on higher vert counts, consider relying on the header, ignore the guy below
      edgeCount+=3; //!< We could've just stripped the vert count right from the header but its safer this way
 	  int raw_vertIndexes[3];
 	  raw_vertIndexes[0] = stoi(raw_value);
 	  line2 >> raw_value;
 	  raw_vertIndexes[1] = stoi(raw_value);
 	  line2 >> raw_value;
 	  raw_vertIndexes[2] = stoi(raw_value);
 
 	  Renderer::CoreUtils::Vertex* vertexPoolVerts[3];
 	  vertexPoolVerts[0] = vertexPoolRef[raw_vertIndexes[0] - 1];
 	  vertexPoolVerts[1] = vertexPoolRef[raw_vertIndexes[1] - 1];
 	  vertexPoolVerts[2] = vertexPoolRef[raw_vertIndexes[2] - 1];
 
 	  std::cout << "VertexPool Vertex MEM ADDR: " << vertexPoolVerts[0] << " [" << vertexPoolVerts[0]->x << ", " << vertexPoolVerts[0]->y << ", " << vertexPoolVerts[0]->z << '\n';
 	  std::cout << "VertexPool Vertex MEM ADDR: " << vertexPoolVerts[1] << " [" << vertexPoolVerts[1]->x << ", " << vertexPoolVerts[1]->y << ", " << vertexPoolVerts[1]->z << '\n';
 	  std::cout << "VertexPool Vertex MEM ADDR: " << vertexPoolVerts[2] << " [" << vertexPoolVerts[2]->x << ", " << vertexPoolVerts[2]->y << ", " << vertexPoolVerts[2]->z << '\n';
 
 	  EdgeData.push_back(new Renderer::CoreUtils::Edge(*vertexPoolVerts[0], *vertexPoolVerts[1]));
 	  EdgeData.push_back(new Renderer::CoreUtils::Edge(*vertexPoolVerts[1], *vertexPoolVerts[2]));
      EdgeData.push_back(new Renderer::CoreUtils::Edge(*vertexPoolVerts[2], *vertexPoolVerts[0]));
 	 } // raw_value.compare("f") != 0
   }   // while(line2 >> raw_value)
  } // if(line[0] == 'f') 
  } // if (!std::getline(*m_input, line)) else
  } // while not eof
  } // while input buffer
 m_input->close();
 return EdgeData;
 };
 
 MeshContainer ModelFile::ExtractMeshData(std::vector<Renderer::CoreUtils::Vertex*>& vertexPoolRef)
 {
  MeshContainer MeshData;
  std::string line;
 
  if (m_input && *m_input)
  {
   //std::cout << "FILE DUMP: " << m_input->rdbuf()<<'\n';
   std::string owningMesh = "ROOT";
   MeshData.AddMesh(new Renderer::CoreUtils::Mesh(owningMesh));
   //std::vector<Core::Renderer::CoreUtils::Mesh*> MeshData;
   int meshIndex = 0;
 
   while (!m_input->eof())
   {
 	if (!getline(*m_input, line))
 	{
 	 std::cout << "END_OF_FILE" << std::endl;
 	}
 	else
 	{
 	 if (line[0] == '#')
 	 {
 	  std::string raw_value;
 	  std::stringstream line2(line);
 	  while (line2 >> raw_value)
 	  {
 	   line2 >> raw_value;
 	   if (raw_value.compare("object") == 0)
 	   {
 		line2 >> raw_value;
 		owningMesh = raw_value;
 		meshIndex++;
 
 		MeshData.AddMesh(new Renderer::CoreUtils::Mesh(owningMesh));
 	   }
 	   break;
 	  }
 	 }
 
 	if (line[0] == 'v')
 	{
 	 std::string raw_value;
 	 std::stringstream line2(line);
 	 while (line2 >> raw_value)
 	 {
 	  if (raw_value.compare("v") != 0)
 	  {
 	   float raw_coordinates[3];
 	   raw_coordinates[0] = stof(raw_value) * AMPLIFICATION_FACTOR + TEMP_OFFSETX;
 	   line2 >> raw_value;
 	   raw_coordinates[1] = stof(raw_value) * AMPLIFICATION_FACTOR + TEMP_OFFSETY;
 	   line2 >> raw_value;
 	   raw_coordinates[2] = stof(raw_value);
 
 	   //Begin Glorious Hack
 	   Renderer::CoreUtils::Vertex* vertex[1];
 	   vertex[0] = new Renderer::CoreUtils::Vertex(raw_coordinates);
 	   vertexPoolRef.push_back(vertex[0]);
 	   MeshData.GetMesh(owningMesh)->AddVertices(vertex, 1);
 	   //End of Glorious Hack
 	   }
 	  }
 	}

  if (line[0] == 'f')
  {
   //!< we reached a new object. if a previous one existed,
   //!< its vert data is fully loaded now so compute pivot
   if (MeshData.length() > 0)
   MeshData.GetMesh(owningMesh)->InitPivot();
 
   std::string raw_value;
   std::stringstream line2(line);
   while (line2 >> raw_value)
   {
 	if (raw_value.compare("f") != 0)
 	{
 	 int raw_vertIndexes[3];
 	 raw_vertIndexes[0] = stoi(raw_value);
 	 line2 >> raw_value;
 	 raw_vertIndexes[1] = stoi(raw_value);
 	 line2 >> raw_value;
 	 raw_vertIndexes[2] = stoi(raw_value);
 
 	 Renderer::CoreUtils::Vertex* vertexPoolVerts[3];
 	 vertexPoolVerts[0] = vertexPoolRef[raw_vertIndexes[0] - 1];
 	 vertexPoolVerts[1] = vertexPoolRef[raw_vertIndexes[1] - 1];
 	 vertexPoolVerts[2] = vertexPoolRef[raw_vertIndexes[2] - 1];
 
 	 Renderer::CoreUtils::Edge* edgeArray[3];
 	 edgeArray[0] = new Renderer::CoreUtils::Edge(*vertexPoolVerts[0], *vertexPoolVerts[1]);
 	 edgeArray[1] = new Renderer::CoreUtils::Edge(*vertexPoolVerts[1], *vertexPoolVerts[2]);
 	 edgeArray[2] = new Renderer::CoreUtils::Edge(*vertexPoolVerts[2], *vertexPoolVerts[0]);
 	 
 	 MeshData.GetMesh(owningMesh)->AddEdges(edgeArray, 3);
 
 	 //Begin Another Glorious Hack!
 	 Renderer::CoreUtils::Triangle* triangle[1];
 	 triangle[0] = new Renderer::CoreUtils::Triangle(edgeArray);
 	 MeshData.GetMesh(owningMesh)->AddTriangles(triangle, 1);
 	 //End of Another Glorious Hack
 	} // if (raw_value.compare("f") != 0)
 }    // while (line2 >> raw_value)
 }    // line[0] == 'f'
 }    // if not getline
}     // while not eof
}     // while input buffer
 m_input->close();
 return MeshData;
 };
 
 ModelFile::~ModelFile()
 {
  delete m_input;
  m_input = nullptr;
 };

} // IO
} // Core
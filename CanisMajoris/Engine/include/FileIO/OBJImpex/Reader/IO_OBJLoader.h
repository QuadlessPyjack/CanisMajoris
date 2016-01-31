#ifndef IO_OBJLOADER_H
#define IO_OBJLOADER_H
////////////////////////////////////////// 
//! \brief   IO_OBJLoader - Canis Majoris Renderer
//! \author  Bogdan Vitel
//! \details OBJ File Loader Header
//! \date    10/11/2014
//! \todo 
//////////////////////////////////////////
#include<EngineDllExport.h>

#include<fstream>
#include<vector>

#include<Utils/MeshContainer.h>

#include<Renderer/CoreUtils/Primitives/Vertex.h>
#include<Renderer/CoreUtils/Primitives/Edge.h>

//namespace  Renderer{
//namespace CoreUtils{
//	class Vertex;
//	class Edge;
//}
//}

namespace Core
{
	namespace IO
	{
		class CM_ENGINE_API ModelFile
		{
		public:
			ModelFile();
			~ModelFile();

			ModelFile(const std::string filePath);

			void Load(const std::string filePath);
			void Save(const std::string filePath);

			bool IsValid();

			std::vector<Renderer::CoreUtils::Vertex*> ExtractVertexData(int& vertCount, MeshContainer& MeshData);
			std::vector<Renderer::CoreUtils::Edge*> ExtractEdgeData(int& edgeCount, std::vector<Renderer::CoreUtils::Vertex*>& vertexPoolRef);
			MeshContainer ExtractMeshData(std::vector<Renderer::CoreUtils::Vertex*>& vertexPoolRef);

		private:
			std::ifstream* m_input;
			std::string m_filename;
		};
	}
}

#endif
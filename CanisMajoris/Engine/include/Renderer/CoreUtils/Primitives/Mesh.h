#ifndef MESH_H
#define MESH_H
////////////////////////////////////////// 
//! \brief   Mesh - Canis Majoris Renderer
//!	\author  Bogdan Vitel
//! \details Mesh class header
//! \date    13/11/2014
//! \todo To be determined
//////////////////////////////////////////
#include<EngineDllExport.h>

#include<vector>

#include<Renderer/CoreUtils/Primitives/Triangle.h>

namespace Core{
	namespace Renderer
	{
		namespace CoreUtils
		{

			class CM_ENGINE_API Mesh
			{
			public:
				Mesh();
				explicit Mesh(const std::string& ID);
				Mesh(const std::string& ID,
					 SDL_Surface* surface,
					 std::vector<Vertex*> vertArray,
					 std::vector<Edge*> edgeArray,
					 std::vector<Triangle*> triArray);

				const std::string& GetID();
				void SetID(const std::string& ID);

				void AddRawVertex(float coordArray[]);

				void AddVertices(Vertex* vertArray[], int vertCount);
				void AddEdges(Edge* edgeArray[], int edgeCount);
				void AddTriangles(Triangle* triangleArray[], int triCount);

				std::vector<Vertex*> GetVertices();
				std::vector<Edge*> GetEdges();
				std::vector<Triangle*> GetTriangles();

				void Draw();

				void SetPivot(Vector3 pivotCoords);
				void InitPivot(); //!< determines mesh centroid and sets pivot
				const Vector3 Location();
				void Translate(Vector3 offset);
				void Scale(Vector3 centre, float scaleFactor);
				void Scale(float scaleFactor);
				void Rotate(Vector3 centre, Vector3 amount);
				void Rotate(Vector3 amount);

				~Mesh();
			private:
				std::string meshID;
				SDL_Surface* m_surface;
				std::vector<Vertex*> m_localVerts;
				std::vector<Edge*> m_localEdges;
				std::vector<Triangle*> m_localTris;

				int m_triCount;
				int m_vertCount;
				Vector3 m_pivot;
			};
		}
	}
}
#endif
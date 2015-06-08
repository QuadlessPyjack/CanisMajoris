////////////////////////////////////////// 
//! \brief   Triangle - Canis Majoris Renderer
//!	\author  Bogdan Vitel
//! \details Triangle class src
//! \date    08/11/2014
//! \todo Implement edge and vertex reference counting
//////////////////////////////////////////


#include<Renderer/CoreUtils/Primitives/Triangle.h>

namespace Core
{
	namespace Renderer
	{
		namespace CoreUtils
		{
			Triangle::Triangle() :
				m_edgeA(new Edge()),
				m_edgeB(new Edge()),
				m_edgeC(new Edge())
			{};

			Triangle::Triangle(Vertex& vertA, Vertex& vertB, Vertex& vertC) :
				m_edgeA(new Edge(vertA, vertB)),
				m_edgeB(new Edge(vertB, vertC)),
				m_edgeC(new Edge(vertC, vertA))
			{};

			Triangle::Triangle(Vertex* triangleVerts[3]) :
				m_edgeA(new Edge(*triangleVerts[0], *triangleVerts[1])),
				m_edgeB(new Edge(*triangleVerts[1], *triangleVerts[2])),
				m_edgeC(new Edge(*triangleVerts[2], *triangleVerts[0]))
			{};

			Triangle::Triangle(Edge& edgeA, Edge& edgeB, Edge& edgeC) :
				m_edgeA(&edgeA),
				m_edgeB(&edgeB),
				m_edgeC(&edgeC)
			{};

			Triangle::Triangle(Edge* triangleEdges[3]) :
				m_edgeA(triangleEdges[0]),
				m_edgeB(triangleEdges[1]),
				m_edgeC(triangleEdges[2])
			{};

			std::vector<const Vertex*> Triangle::GetVertices()
			{
				std::vector<const Vertex*> tri_verts;
				tri_verts.push_back(m_edgeA->GetEdgeVertex(0));
				tri_verts.push_back(m_edgeB->GetEdgeVertex(0));
				tri_verts.push_back(m_edgeC->GetEdgeVertex(0));

				return tri_verts;
			}

			void Triangle::Draw()
			{
				Triangle::m_edgeA->Draw();
				Triangle::m_edgeB->Draw();
				Triangle::m_edgeC->Draw();
			}

			void Triangle::Translate(Vector3 offset)
			{
				m_edgeA->Translate(offset);
				m_edgeB->Translate(offset);
				m_edgeC->Translate(offset);
			}

			Triangle::~Triangle()
			{
				m_edgeA = nullptr;
				delete m_edgeA;
				m_edgeA = nullptr;

				m_edgeB = nullptr;
				delete m_edgeB;
				m_edgeB = nullptr;

				m_edgeC = nullptr;
				delete m_edgeC;
				m_edgeC = nullptr;
			};

		}
	}
}
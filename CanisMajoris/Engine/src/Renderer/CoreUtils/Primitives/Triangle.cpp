////////////////////////////////////////// 
//! \brief   Triangle - Canis Majoris Renderer
//!	\author  Bogdan Vitel
//! \details Triangle class src
//! \date    08/11/2014
//! \todo Implement edge and vertex reference counting
//////////////////////////////////////////


#include<Renderer/CoreUtils/Primitives/Triangle.h>

namespace Core      {
namespace Renderer  {
namespace CoreUtils {

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
	 m_edgeC(new Edge(*triangleVerts[2], *triangleVerts[0])),
	 m_normal(0,0,0)
	{
		Vector3 u = triangleVerts[1]->Location() - triangleVerts[0]->Location();
		Vector3 v = triangleVerts[2]->Location() - triangleVerts[0]->Location();
	
		m_normal = Vector3::Cross(u, v);
	};
	
	Triangle::Triangle(Edge& edgeA, Edge& edgeB, Edge& edgeC) :
	 m_edgeA(&edgeA),
	 m_edgeB(&edgeB),
	 m_edgeC(&edgeC)
	{
		Vector3 u = edgeA.GetEdgeVertex(1)->Location() - edgeA.GetEdgeVertex(0)->Location();
		Vector3 v = edgeC.GetEdgeVertex(0)->Location() - edgeC.GetEdgeVertex(1)->Location();
	
		m_normal = Vector3::Cross(u, v);
	};
	
	Triangle::Triangle(Edge* triangleEdges[3]) :
	 m_edgeA(triangleEdges[0]),
	 m_edgeB(triangleEdges[1]),
	 m_edgeC(triangleEdges[2])
	{
	}
	
	void Triangle::setEdges(Edge* triangleEdges[3])
	{
		m_edgeA = triangleEdges[0];
		m_edgeB = triangleEdges[1];
		m_edgeC = triangleEdges[2];
	
		Vector3 u = m_edgeA->GetEdgeVertex(1)->Location() - m_edgeA->GetEdgeVertex(0)->Location();
		Vector3 v = m_edgeC->GetEdgeVertex(0)->Location() - m_edgeC->GetEdgeVertex(1)->Location();
	
		m_normal = Vector3::Cross(u, v);
	}
	
	void Triangle::setID(int id)
	{
		m_id = id;
	}
	
	int Triangle::ID() const
	{
		return m_id;
	}
	
	Vector3 Triangle::Normal()
	{
		if (m_normal == Vector3::Zero())
		{
			Vector3 u = m_edgeA->GetEdgeVertex(1)->Location() - m_edgeA->GetEdgeVertex(0)->Location();
			Vector3 v = m_edgeC->GetEdgeVertex(0)->Location() - m_edgeC->GetEdgeVertex(1)->Location();
	
			m_normal = Vector3::Cross(u, v);
		}
	
		const Vector3 normal = m_normal;
		return normal;
	}
	
	std::vector<const Vertex*> Triangle::GetVertices()
	{
		if (m_edgeA->GetEdgeVertex(0)->id() == m_edgeB->GetEdgeVertex(0)->id() ||
			m_edgeB->GetEdgeVertex(0)->id() == m_edgeC->GetEdgeVertex(0)->id() ||
			m_edgeA->GetEdgeVertex(0)->id() == m_edgeC->GetEdgeVertex(0)->id())
		{
			//std::cout << "Incoherent triangle found. Reordering edges." << std::endl;
			reorderEdges();
		}

		std::vector<const Vertex*> tri_verts;
		tri_verts.push_back(m_edgeA->GetEdgeVertex(0));
		tri_verts.push_back(m_edgeB->GetEdgeVertex(0));
		tri_verts.push_back(m_edgeC->GetEdgeVertex(0));

		return tri_verts;
	}
	
	void Triangle::Draw(Vector3 colour)
	{
		m_edgeA->Draw(colour);
		m_edgeB->Draw(colour);
		m_edgeC->Draw(colour);
	}
	
	void Triangle::Translate(Vector3 offset)
	{
		m_edgeA->Translate(offset);
		m_edgeB->Translate(offset);
		m_edgeC->Translate(offset);
	
		Vector3 u = m_edgeA->GetEdgeVertex(1)->Location() - m_edgeA->GetEdgeVertex(0)->Location();
		Vector3 v = m_edgeC->GetEdgeVertex(0)->Location() - m_edgeC->GetEdgeVertex(1)->Location();
	
		m_normal = Vector3::Cross(u, v);
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
	}

	void Triangle::reorderEdges()
	{
		//        A           AB
		//       /\           BC
		//      /  \          CA
		//     /    \         01
		//    /      \
		//   B -------C

		// edgeB = AC
		if (m_edgeA->GetEdgeVertex(0)->id() == m_edgeB->GetEdgeVertex(0)->id())
		{
			m_edgeB->flipEdge(); // edgeB is now CA, switch with edgeC

			Edge* e = m_edgeB;
			
			m_edgeB = m_edgeC;
			m_edgeC = e;
		}

		// edgeC = BA
		if (m_edgeB->GetEdgeVertex(0)->id() == m_edgeC->GetEdgeVertex(0)->id())
		{
			m_edgeC->flipEdge(); // edgeC is now AB, switch with edgeA

			Edge* e = m_edgeC;

			m_edgeC = m_edgeA;
			m_edgeA = e;
		}

		// edgeC = AC
		if (m_edgeC->GetEdgeVertex(0)->id() == m_edgeA->GetEdgeVertex(0)->id())
		{
			m_edgeC->flipEdge();
		}

		// AB, CB ---> AB, BC
		if (m_edgeA->GetEdgeVertex(1)->id() == m_edgeB->GetEdgeVertex(1)->id())
		{
			m_edgeB->flipEdge();
		}

		// BC, AC ----> BC, CA
		if (m_edgeB->GetEdgeVertex(1)->id() == m_edgeC->GetEdgeVertex(1)->id())
		{
			m_edgeC->flipEdge();
		}

		// CA, BA -----> CA, AB
		if (m_edgeC->GetEdgeVertex(1)->id() == m_edgeA->GetEdgeVertex(1)->id())
		{
			m_edgeA->flipEdge();
		}
	}

} // CoreUtils
} // Renderer
} // Core
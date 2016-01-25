#ifndef TRIANGLE_H
#define TRIANGLE_H
////////////////////////////////////////// 
//! \brief   Triangle - Canis Majoris Renderer
//!	\author  Bogdan Vitel
//! \details Triangle class header
//! \date    08/11/2014
//! \todo Group duplicate base methods into a virtual class
//////////////////////////////////////////

#include<Renderer/CoreUtils/Primitives/Edge.h>

namespace Core     {
namespace Renderer {
namespace CoreUtils{
 class CM_ENGINE_API Triangle
 {
 public:
 Triangle();
 
 Triangle(Vertex& vertA, Vertex& vertB, Vertex& vertC);
 explicit Triangle(Vertex* triangleVerts[3]);
 
 Triangle(Edge& edgeA, Edge& edgeB, Edge& edgeC);
 explicit Triangle(Edge* triangleEdges[3]);
 
 void Draw();
 
 std::vector<const Vertex*> GetVertices();
 void Translate(Vector3 offset);
 
 ~Triangle();
 
 private:
 Edge* m_edgeA;
 Edge* m_edgeB;
 Edge* m_edgeC;
 };
} // CoreUtils
} // Renderer 
} // Core

#endif // TRIANGLE_H

#ifndef EDGE_H
#define EDGE_H
////////////////////////////////////////// 
//! \brief   Edge - Canis Majoris Renderer
//!	\author  Bogdan Vitel
//! \details Edge class header
//! \date    07/11/2014
//! \todo To be determined
//////////////////////////////////////////
#include<Renderer/CoreUtils/Primitives/Vertex.h>

namespace Core      {
namespace Renderer  {
namespace CoreUtils {

// forward declarations
class Mesh;

class CM_ENGINE_API Edge
{
public:
 Edge();
 Edge(Vertex& startVert, Vertex& endVert);
 Edge(Vertex& startVert, Vertex& endVert, int edgeIndex);
 explicit Edge(Vertex* edgeVerts[]);
 int index() const;

 void setIndex(int i);
 // warning! once both owner triangles are set, THAT'S IT
 // if you DO want to change the edge owners, you're either insane or working on OpenRedFaction
 void setParentTriangle(int triangleID);
 void Draw();
 void Translate(Vector3 offset);

 const Vertex* GetEdgeVertex(int index);
 const int GetEdgeOwner(int owner = 0);

 ~Edge();
private:
 int m_ownerTriangleIDs[2];
 int m_index;
 const Mesh* m_mesh_owner;
 Vertex* m_startVert;
 Vertex* m_endVert;
 SDL_Surface* m_SDLSurface;
};

} // CoreUtils
} // Renderer
} // Core

#endif // EDGE_H
////////////////////////////////////////// 
//! \brief   Edge - Canis Majoris Renderer
//!	\author  Bogdan Vitel
//! \details Edge class src
//! \date    07/11/2014
//! \todo Consider constructor with existing vertices
//////////////////////////////////////////

#include<Renderer/CoreUtils/Primitives/Edge.h>
#include<Renderer/CoreUtils/Scene.h>
#include<Renderer/CoreUtils/Camera.h>

#include<Utils/Validators.inl>
#include<Utils/Math/ConverterUtils.inl>
#include<string>
#include<vector>
#include<map>
#include <list>

namespace {
	void DrawEdgeToScreen(const Vertex &startVert, const Vertex &endVert)
	{
		Vector2 uiStartVert(startVert.x, SCREEN_HEIGHT - startVert.y);
		Vector2 uiEndVert(endVert.x, SCREEN_HEIGHT - endVert.y);

		SDL_PixelFormat* fmt = Scene::GetInstance().GetViewport()->format;
		if (ValidateScreenCoord(uiStartVert) && ValidateScreenCoord(uiEndVert))
		{
			Draw_Line(Scene::GetInstance().GetViewport(), uiStartVert.x, uiStartVert.y, uiEndVert.x, uiEndVert.y, SDL_MapRGB(fmt, 0, 255, 0));
			fmt = nullptr;
			delete fmt;
		}
	}
}


namespace Core      {
namespace Renderer  {
namespace CoreUtils {

Edge::Edge() :
m_index(0),
m_mesh_owner(nullptr),
m_startVert(new Vertex()),
m_endVert(new Vertex()),
m_SDLSurface(Scene::GetInstance().GetViewport())
{};

Edge::Edge(Vertex& startVert, Vertex& endVert) :
m_index(0),
m_mesh_owner(nullptr),
m_startVert(&startVert),
m_endVert(&endVert),
m_SDLSurface(Scene::GetInstance().GetViewport())
{};

Edge::Edge(Vertex& startVert, Vertex& endVert, int edgeIndex) :
m_index(edgeIndex),
m_mesh_owner(nullptr),
m_startVert(&startVert),
m_endVert(&endVert),
m_SDLSurface(Scene::GetInstance().GetViewport())
{};

Edge::Edge(Vertex* edgeVerts[2]) :
m_index(0),
m_mesh_owner(nullptr),
m_startVert(edgeVerts[0]),
m_endVert(edgeVerts[1]),
m_SDLSurface(Scene::GetInstance().GetViewport())
{};

int Edge::index() const
{
	return m_index;
}

const Vertex* Edge::GetEdgeVertex(int index)
{
if (index == 1)
 return m_endVert;

 return m_startVert;
}

const int Edge::GetEdgeOwner(int owner)
{
	if (owner < 0 || owner > 1)
	{
		return m_ownerTriangleIDs[0];
	}

	return m_ownerTriangleIDs[owner];
}

	void Edge::setIndex(int i)
{
	m_index = i;
}

//! @brief Sets the triangle IDs of the faces that share this edge
//! @note  The laws of this Universe forbid edges from being shared by more than two faces
//! @param triangleID The ID of the face that owns this edge
void Edge::setParentTriangle(int triangleID)
{
	if (m_ownerTriangleIDs[0] == 0)
	{
		m_ownerTriangleIDs[0] = triangleID;
		return;
	}

	m_ownerTriangleIDs[1] = triangleID;
	return;
}

	void Edge::Draw()
{

 if(m_startVert->GetOwner() != m_endVert->GetOwner())
 {
 	// Uhm... we have a serious problem here
 	// Log and stop rendering this edge
 	std::string conflictingMesh1 = m_startVert->GetOwner();
 	std::string conflictingMesh2 = m_endVert->GetOwner();
 	//std::cout << "Malformed geometry detected between meshes " << conflictingMesh1 << " and " << conflictingMesh2 << std::endl;
 	return;
 }


 if (m_startVert->GetOwner().find("f_") == 0)
 {
	// Treat this 3D geometry as an interface font and render directly to screen surface
	 DrawEdgeToScreen(*m_startVert, *m_endVert);
	 return;
 }

// 3D World Space Projection Handling
 SDL_PixelFormat* fmt = m_SDLSurface->format;

 Vector3 CameraPoz = Scene::GetInstance().GetCamera()->Location();
 Vector3 CamRelStartV3 = WorldToCameraCoords(m_startVert->Location());
 Vector3 CamRelEndV3 = WorldToCameraCoords(m_endVert->Location());

 float x_screen1 = (CamRelStartV3.x / CamRelStartV3.z) * SCREEN_WIDTH /* 1.5f*/  + SCREEN_WIDTH  / 2.0f;// *SCREEN_WIDTH + SCREEN_WIDTH / 2;
 float y_screen1 = (CamRelStartV3.y / CamRelStartV3.z) * SCREEN_HEIGHT /* 1.5f*/ + SCREEN_HEIGHT / 2.0f;// *SCREEN_HEIGHT + SCREEN_HEIGHT / 2;
 
 float x_screen2 = (CamRelEndV3.x / CamRelEndV3.z) * SCREEN_WIDTH /* 1.5f*/  + SCREEN_WIDTH  / 2.0f;// *SCREEN_WIDTH + SCREEN_WIDTH / 2;
 float y_screen2 = (CamRelEndV3.y / CamRelEndV3.z) * SCREEN_HEIGHT /* 1.5f*/ + SCREEN_HEIGHT / 2.0f;// *SCREEN_HEIGHT + SCREEN_HEIGHT / 2;
 
 Vector2 screen_start(x_screen1, y_screen1);
 Vector2 screen_end(x_screen2, y_screen2);
//				std::cout << "[EDGE_DBG] SSTART: " << screen_start << " SEND: " << screen_end << "MEM ADDR: " << m_startVert << " " << m_endVert << std::endl;
//				std::cout << "--------------------------" << std::endl;
 if (ValidateScreenCoord(screen_start) && ValidateScreenCoord(screen_end))
 {
	 if (m_startVert->GetOwner().find("calibration_marker") == 0)
	 {
		 Draw_Line(m_SDLSurface, screen_start.x, screen_start.y, screen_end.x, screen_end.y, SDL_MapRGB(fmt, 255, 0, 255));
		 fmt = nullptr;
		 delete fmt;

		 return;
	 }

	 Draw_Line(m_SDLSurface, screen_start.x, screen_start.y, screen_end.x, screen_end.y, SDL_MapRGB(fmt, 255, 0, 0));
	 fmt = nullptr;
	 delete fmt;
 }

 // UI Surface Projection Handling


}

void Edge::Translate(Vector3 offset)
{
 if (ValidateScreenCoord(*m_startVert) && ValidateScreenCoord(*m_endVert))
 {
  m_startVert->Translate(offset);
  m_endVert->Translate(offset);
 }
}

Edge::~Edge()
{
 m_startVert = nullptr;
 delete m_startVert;
 m_startVert = nullptr;

 m_endVert = nullptr;
 delete m_endVert;
 m_endVert = nullptr;
}

} // CoreUtils
} // Renderer
} // Core
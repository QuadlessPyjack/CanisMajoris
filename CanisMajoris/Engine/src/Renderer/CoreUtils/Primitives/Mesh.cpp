////////////////////////////////////////// 
//! \brief   Mesh - Canis Majoris Renderer
//!	\author  Bogdan Vitel
//! \details Mesh class src
//! \date    13/11/2014
//! \todo SetSurface deprecated across hierarchy.
//!       Use Scene::GetInstance().GetViewport() instead.
//////////////////////////////////////////

#include<Renderer/CoreUtils/Primitives/Mesh.h>

#include<Renderer/CoreUtils/Scene.h>
#include<Utils/Validators.inl>
#include <list>
#include <map>


namespace Core      {
namespace Renderer  {
namespace CoreUtils {

namespace
{
	//! This is the embryonic form of the FXProcessor system
	//! \todo Move these into the FXProcessor system
	std::list<Edge*> FXContourEffect(std::vector<Edge*> edges/*, std::vector<Vertex*> positions*/)
	{
		std::list<Edge*> resultList;
		std::vector<Edge*>::const_iterator it;
		for (it = edges.begin(); it != edges.end(); ++it)
		{
			if((*it)->GetEdgeOwner(1) == 0 || (*it)->GetEdgeOwner(0) == 0)
			{
				resultList.push_front(*it);
			}
		}
	return resultList;
	}

	void ProcessScreenEffects(std::vector<Edge*> targetEdges)
	{
		std::list<Edge*> preprocessedEdges = FXContourEffect(targetEdges);
		for (std::list<Edge*>::const_iterator it = preprocessedEdges.begin(); it != preprocessedEdges.end(); ++it)
		{
			//! \todo Allow Specification of colour and thickness parameters
			(*it)->Draw();
		}
	}
}

Mesh::Mesh() :
 meshID("NULL"),
 m_surface(Scene::GetInstance().GetViewport()),
 m_localVerts(NULL),
 m_localEdges(NULL),
 m_localTris(NULL),
 m_triCount(0),
 m_vertCount(0),
 m_isLocked(false)
{};

Mesh::Mesh(const std::string& ID) :
 meshID(ID),
 m_surface(Scene::GetInstance().GetViewport()),
 m_localVerts(NULL),
 m_localEdges(NULL),
 m_localTris(NULL),
 m_triCount(0),
 m_vertCount(0),
 m_isLocked(false)
{};

Mesh::Mesh(const std::string& ID,
 SDL_Surface* surface, //! DEPRECATED
 std::vector<Vertex*> vertArray,
 std::vector<Edge*> edgeArray,
 std::vector<Triangle*> triArray) :
 
 meshID(ID),
 m_surface(Scene::GetInstance().GetViewport()),
 m_localVerts(vertArray),
 m_localEdges(edgeArray),
 m_localTris(triArray),
 m_triCount(triArray.size()),
 m_vertCount(vertArray.size()),
 m_isLocked(false)
{
 for (int i = 0; i < m_vertCount; ++i)
 {
	m_localVerts[i]->SetOwner(meshID);
 }
};

const std::string& Mesh::GetID()
{
 return meshID;
};

void Mesh::SetID(const std::string& ID)
{
 meshID = ID;
}

void Mesh::SetLocked(bool lockFlag)
{
	m_isLocked = lockFlag;
}

bool Mesh::IsLocked()
{
	return m_isLocked;
};

void Mesh::AddRawVertex(float coordArray[])
{
 m_localVerts.push_back(new Vertex(coordArray[0], coordArray[1], coordArray[2]));
 m_localVerts.back()->SetOwner(meshID);
};

void Mesh::AddVertices(Vertex* vertArray[], int vertCount)
{
 for (int i = 0; i < vertCount; ++i)
 {
  vertArray[i]->SetOwner(meshID);
  m_localVerts.push_back(vertArray[i]);
 }
 m_vertCount += vertCount;
};

void Mesh::AddEdge(Edge* edge)
{
	m_localEdges.push_back(edge);
};

void Mesh::AddEdges(Edge* edgeArray[], int edgeCount)
{
 for (int i = 0; i < edgeCount; ++i)
 {
  m_localEdges.push_back(edgeArray[i]);
 }
};
void Mesh::AddTriangles(Triangle* triangleArray[], int triCount)
{
 for (int i = 0; i < triCount; ++i)
 {
  m_localTris.push_back(triangleArray[i]);
 }
 m_triCount += triCount;
};

std::vector<Vertex*> Mesh::GetVertices()
{
 return m_localVerts;
};

const std::vector<Edge*> &Mesh::GetEdges()
{
 return m_localEdges;
};

std::vector<Triangle*> Mesh::GetTriangles()
{
 return m_localTris;
};

void Mesh::Draw()
{
	//! \todo Move all of this into its own FXProcessor Manager class
	// special rendering case, handled separately
	if (meshID.find("f_") == 0)
	{
		ProcessScreenEffects(m_localEdges);
		return;
	}

	if (m_triCount > 0)
	{
		for (int i = 0; i < m_triCount; ++i)
		{
			m_localTris[i]->Draw();
		}
	}
//! DEBUG ONLY - REMOVE WHEN DONE
if (meshID != "ROOT" && "NULL")
{
	SDL_PixelFormat* fmt = m_surface->format;
	if (ValidateScreenCoord(m_wsPivot.x, 0) && ValidateScreenCoord(m_wsPivot.y, 1))
	{
		Draw_FillCircle(Scene::GetInstance().GetViewport(), m_wsPivot.x, m_wsPivot.y, 1, SDL_MapRGB(fmt, 0, 0, 255));
		//std::cout << "Pivot is at: X: " << m_wsPivot.x << " Y: " << m_wsPivot.y << std::endl;
		fmt = nullptr;
		delete fmt;
	}
}
};

void Mesh::SetPivot(Vector3 pivotCoords)
{
 m_wsPivot = pivotCoords;
};

void Mesh::InitPivot() //!< determines mesh centroid and sets pivot
{
Vector3 rawCoords;
if (m_vertCount > 0)
{
 for (int i = 0; i < m_vertCount; ++i)
 {
  rawCoords.x += m_localVerts[i]->x;
  rawCoords.y += m_localVerts[i]->y;
  rawCoords.z += abs(m_localVerts[i]->z);
 }
rawCoords.x /= m_vertCount;
rawCoords.y /= m_vertCount;
rawCoords.z /= m_vertCount;
}

m_wsPivot = rawCoords;
m_pivot = m_wsPivot;
};

const Vector3 Mesh::Location()
{
 return m_wsPivot;
}

void Mesh::SetLocation(Vector3 location)
{
	if (m_vertCount > 0)
	{
		for (int i = 0; i < m_vertCount; ++i)
		{
			Vector3 prevLocation = m_localVerts[i]->Location();
			Vector3 newLocation = location + prevLocation - m_pivot;
			m_localVerts[i]->SetLocation(newLocation);
		}
	}

	m_wsPivot = location;
}

void Mesh::Translate(Vector3 offset)
{
 if (m_vertCount > 0)
 {
  for (int i = 0; i < m_vertCount; ++i)
  {
   m_localVerts[i]->Translate(offset);
  }
 }
};

void Mesh::Scale(Vector3 centre, float scaleFactor)
{
if (m_vertCount > 0)
{
 for (int i = 0; i < m_vertCount; ++i)
 {
  m_localVerts[i]->Scale(centre, scaleFactor);
 }
}
};

void Mesh::Scale(float scaleFactor)
{
if (m_vertCount > 0)
 {
 for (int i = 0; i < m_vertCount; ++i)
  {
  m_localVerts[i]->Scale(m_wsPivot, scaleFactor);
  }
 }
};

void Mesh::Rotate(Vector3 centre, Vector3 amount)
{
if (m_vertCount > 0)
{
 for (int i = 0; i < m_vertCount; ++i)
 {
 m_localVerts[i]->Rotate(centre, amount);
 }
}			
};

void Mesh::Rotate(Vector3 amount)
{
 if (m_vertCount > 0)
 {
  for (int i = 0; i < m_vertCount; ++i)
  {
  m_localVerts[i]->Rotate(m_wsPivot, amount);
  }
 }
}

void Mesh::ResetTransform()
{
	if (m_vertCount > 0)
	{
		for (int i = 0; i < m_vertCount; ++i)
		{
			m_localVerts[i]->ResetTransform();
		}
	}

	m_wsPivot = m_pivot;
};

Mesh::~Mesh()
{
 m_surface = nullptr;
 delete m_surface;
};

} // CoreUtils
} // Renderer
} // Core
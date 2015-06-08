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

namespace Core
{
	namespace Renderer
	{
		namespace CoreUtils
		{
			Edge::Edge() :
				m_startVert(new Vertex()),
				m_endVert(new Vertex()),
				m_SDLSurface(Scene::GetInstance().GetViewport())
			{};

			Edge::Edge(Vertex& startVert, Vertex& endVert) :
				m_startVert(&startVert),
				m_endVert(&endVert),
				m_SDLSurface(Scene::GetInstance().GetViewport())
			{};

			Edge::Edge(Vertex* edgeVerts[2]) :
				m_startVert(edgeVerts[0]),
				m_endVert(edgeVerts[1]),
				m_SDLSurface(Scene::GetInstance().GetViewport())
			{};

			const Vertex* Edge::GetEdgeVertex(int index)
			{
				if (index == 1)
					return m_endVert;
				
				return m_startVert;
			};

			void Edge::Draw()
			{
				SDL_PixelFormat* fmt = m_SDLSurface->format;

				Vector3 CameraPoz = Scene::GetInstance().GetCamera()->Location();
				Vector3 CamRelStartV3 = WorldToCameraCoords(m_startVert->Location());
				Vector3 CamRelEndV3 = WorldToCameraCoords(m_endVert->Location());
//				std::cout << "-----------------------------" << std::endl;
//				std::cout << "[EDGE_DBG] STARTVERT: " << m_startVert->x << "," << m_startVert->y;
//				std::cout << " ENDVERT: " << m_endVert->x << "," << m_endVert->y << std::endl;
				float x_screen1 = (CamRelStartV3.x / CamRelStartV3.z) * SCREEN_WIDTH + SCREEN_WIDTH / 2;// *SCREEN_WIDTH + SCREEN_WIDTH / 2;
				float y_screen1 = (CamRelStartV3.y / CamRelStartV3.z) * SCREEN_HEIGHT + SCREEN_HEIGHT / 2;// *SCREEN_HEIGHT + SCREEN_HEIGHT / 2;

				float x_screen2 = (CamRelEndV3.x / CamRelEndV3.z) * SCREEN_WIDTH + SCREEN_WIDTH / 2;// *SCREEN_WIDTH + SCREEN_WIDTH / 2;
				float y_screen2 = (CamRelEndV3.y / CamRelEndV3.z) * SCREEN_HEIGHT + SCREEN_HEIGHT / 2;// *SCREEN_HEIGHT + SCREEN_HEIGHT / 2;

				Vector2 screen_start(x_screen1, y_screen1);
				Vector2 screen_end(x_screen2, y_screen2);
//				std::cout << "[EDGE_DBG] SSTART: " << screen_start << " SEND: " << screen_end << "MEM ADDR: " << m_startVert << " " << m_endVert << std::endl;
//				std::cout << "--------------------------" << std::endl;
				if (ValidateScreenCoord(screen_start) && ValidateScreenCoord(screen_end))
				{
					Draw_Line(m_SDLSurface, screen_start.x, screen_start.y, screen_end.x, screen_end.y, SDL_MapRGB(fmt, 255, 0, 0));
					fmt = nullptr;
					delete fmt;
				}

				//if (ValidateScreenCoord(*m_startVert) && ValidateScreenCoord(*m_endVert))
				//{
				//	Vector3 CameraPoz = Scene::GetInstance().GetCamera()->Location();
				//	Vector3 CamRelStartV3 = WorldToCameraCoords(m_startVert->Location());
				//	Vector3 CamRelEndV3 = WorldToCameraCoords(m_endVert->Location());

				//	float x_screen1 = (CamRelStartV3.x / CamRelStartV3.z) * SCREEN_WIDTH + SCREEN_WIDTH / 2;
				//	float y_screen1 = (CamRelStartV3.y / CamRelStartV3.z) * SCREEN_HEIGHT + SCREEN_HEIGHT / 2;

				//	float x_screen2 = (CamRelEndV3.x / CamRelEndV3.z) * SCREEN_WIDTH + SCREEN_WIDTH / 2;
				//	float y_screen2 = (CamRelEndV3.y / CamRelEndV3.z) * SCREEN_HEIGHT + SCREEN_HEIGHT / 2;
				//	
				//	Draw_Line(m_SDLSurface, x_screen1, y_screen1, x_screen2, y_screen2, SDL_MapRGB(fmt, 255, 0, 0));
				//	//Draw_Line(m_SDLSurface, m_startVert->x, m_startVert->y, m_endVert->x, m_endVert->y, SDL_MapRGB(fmt, 255, 0, 0));

				//	fmt = nullptr;
				//	delete fmt;
				//}
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

		}
	}
}
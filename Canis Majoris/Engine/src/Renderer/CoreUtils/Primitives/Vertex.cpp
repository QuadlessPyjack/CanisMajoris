////////////////////////////////////////// 
//! \brief   Vertex - Canis Majoris Renderer
//! \author	 Bogdan Vitel 
//!	\details Vertex class src
//! \date    07/11/2014
//! \todo You'll probably want to change coordinates via transform methods eventually
////////////////////////////////////////////
#include<Renderer/CoreUtils/Scene.h>

#include<Renderer/CoreUtils/Primitives/Vertex.h>

#include<Utils/Math/Vector2.h>
#include<Utils/Validators.inl>
namespace Core
{
	namespace Renderer
	{
		namespace CoreUtils
		{
			Vertex::Vertex() :
				x(0.0f),
				y(0.0f),
				z(0.0f),
				m_SDLSurface(nullptr)
			{};

			Vertex::Vertex(float pozX, float pozY, float pozZ) :
				x(pozX),
				y(pozY),
				z(pozZ),
				m_v3(Vector3(pozX, pozY, pozZ)),
				m_SDLSurface(nullptr)
			{};

			Vertex::Vertex(float coordinates[3]) :
				x(coordinates[0]),
				y(coordinates[1]),
				z(coordinates[2]),
				m_v3(Vector3(coordinates[0], coordinates[1], coordinates[2])),
				m_SDLSurface(nullptr)
			{};

			void Vertex::SetOwner(std::string ownerName)
			{
				m_meshOwnerName = ownerName;
			};
			const std::string Vertex::GetOwner()
			{
				return m_meshOwnerName;
			};

			void Vertex::Draw()
			{
				SDL_Surface *surface = Scene::GetInstance().GetViewport();
				SDL_PixelFormat* fmt = surface->format;
				if (ValidateScreenCoord(x, 0) && ValidateScreenCoord(y, 1))
				{
					Draw_FillCircle(surface, x, y, 2, SDL_MapRGB(fmt, 255, 0, 0));

					fmt = nullptr;
					delete fmt;
				}
			}

			const Vector3 &Vertex::Location()
			{
				return m_v3;
			}

			void Vertex::Translate(Vector3 offset)
			{
				x += offset.x;
				y += offset.y;
				z += offset.z;

				m_v3 = Vector3(x, y, z);
			}

			void Vertex::Scale(const Vector3& centre, float scaleFactor)
			{
				Vector3 newCoords = centre;
				
				x = (x - centre.x) * scaleFactor + centre.x;
				y = (y - centre.y) * scaleFactor + centre.y;
				z = (z - centre.z) * scaleFactor + centre.z;
				//!>Get those damn pivot coordinates first before implementing this!
				//!>And find a humane way to pass them over to the Vertex class!
			};

			void Vertex::Rotate(const Vector3& centre, Vector3 amount)
			{
				//Begining of Glorious Hack!
				//Apply changes for rotation around Z
				if (amount.z != 0.0f)
				{
					Vector2 rotVect(x - centre.x, y - centre.y);
					rotVect.ToPolar();
					rotVect.x += amount.z;
					rotVect.ToCartesian();

					x = centre.x + rotVect.x;
					y = centre.y + rotVect.y;
				}
				//Apply changes for rotation around Y
				if (amount.y != 0.0f)
				{
					Vector2 rotVect(x - centre.x, z - centre.z);
					rotVect.ToPolar();
					rotVect.x += amount.y;
					rotVect.ToCartesian();
					x = centre.x + rotVect.x;
					z = centre.z + rotVect.y; //which is actually the vertex's Z coordinate
				}

				//Apply changes for rotation around X
				if (amount.x != 0.0f)
				{
					Vector2 rotVect(z - centre.z, y - centre.y);
					rotVect.ToPolar();
					rotVect.x += amount.x;
					rotVect.ToCartesian();

					z = centre.z + rotVect.x;
					y = centre.y + rotVect.y;
				}
				//End of Glorious Hack!
			}

			Vertex::~Vertex()
			{};

		}
	}
}
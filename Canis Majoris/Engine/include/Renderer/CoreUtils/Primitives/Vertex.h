#ifndef VERTEX_H
#define VERTEX_H
////////////////////////////////////////// 
//! \brief   Vertex - Canis Majoris Renderer
//! \author	 Bogdan Vitel
//! \details Vertex class header
//! \date    07/11/2014
//! \todo You'll probably want to change coordinates via transform methods eventually
//////////////////////////////////////////

#include<SDL.h>
#include<SDL_draw.h>
#include<vector>

#include<Utils/Math/Vector3.h>

namespace Core
{
	namespace Renderer
	{
		namespace CoreUtils
		{
			class Vertex
			{
			public:
				Vertex(float pozX, float pozY, float pozZ);
				Vertex(Vector3 v3);
				Vertex(float coordinates[3]);
				Vertex(); //!< \todo Should probably find a way to restrict this

				void SetOwner(std::string ownerName);
				const std::string GetOwner();

				void Draw();

				const Vector3 &Location();
				void Translate(Vector3 offset);
				void Scale(const Vector3& centre, float scaleFactor);
				void Rotate(const Vector3& centre, Vector3 amount);

				~Vertex();

				float x;
				float y;
				float z;

			private:
				SDL_Surface* m_SDLSurface;
				std::string m_meshOwnerName;
				Vector3 m_v3;
			};
		}
	}
}

#endif
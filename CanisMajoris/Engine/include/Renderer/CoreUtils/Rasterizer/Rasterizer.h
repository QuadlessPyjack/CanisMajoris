#ifndef RASTERIZER_H
#define RASTERIZER_H
////////////////////////////////////////// 
//! \brief   Rasterizer - Canis Majoris Renderer
//!	\author  Bogdan Vitel
//! \details Rasterizer header
//! \date    19/12/2014
//! \todo 
//////////////////////////////////////////
#include<EngineDllExport.h>

#include<string>
#include<SDL.h>
#include<SDL_draw.h>

#include<Utils/MeshContainer.h>

namespace Core
{
	namespace Renderer
	{
		namespace CoreUtils
		{
			class Mesh;
			class Triangle;

			class CM_ENGINE_API Rasterizer
			{
			public:
				Rasterizer(MeshContainer &meshPool, SDL_Surface* screen);
				Rasterizer();
				~Rasterizer();
				void RasterizeMesh(Mesh& mesh);
				void RasterizeTriangle(Triangle &tri);
				void RasterizeByMeshID(std::string ID);
				void RasterizeByTriangleID(std::string ID);

			private:
				MeshContainer *m_meshPool;
				Mesh *m_mesh;
				Triangle *m_tri;
				SDL_Surface *m_screen;
				
				void fillFlatTriangle(Bounds rasterBounds, bool mirrorX, bool mirrorY, SDL_Surface* screen);
				void fillTriangle(Bounds rasterBounds, Math::Vector2 thirdCorner, SDL_Surface* screen);
				int* matchTriangleOnBounds(Math::Vector2* trianglePoints, Bounds &rasterBounds);
				float slopeCompare(Math::Vector2 origin, Math::Vector2 point1, Math::Vector2 point2);
			};
		}
	}
}

#endif //RASTERIZER_H
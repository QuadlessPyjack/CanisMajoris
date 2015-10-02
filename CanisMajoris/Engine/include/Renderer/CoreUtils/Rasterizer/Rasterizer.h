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
				~Rasterizer();
				void RasterizeScene();
				void RasterizeMesh(Mesh &mesh);
				void RasterizeTriangle(Triangle &tri);
				void RasterizeByMeshID(std::string ID);
				void RasterizeByTriangleID(std::string ID);

			private:
				MeshContainer *m_meshPool;
				Mesh *m_mesh;
				Triangle *m_tri;
				SDL_Surface *m_screen;
				void fillHalfFlatTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, int orientation, SDL_Surface* screen);
			};
		}
	}
}

#endif //RASTERIZER_H
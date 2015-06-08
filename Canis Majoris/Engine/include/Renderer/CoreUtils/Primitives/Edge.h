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

namespace Core
{
	namespace Renderer
	{
		namespace CoreUtils
		{

			class Edge
			{
			public:
				Edge();
				Edge(Vertex& startVert, Vertex& endVert);
				Edge(Vertex* edgeVerts[]);

				void Draw();
				void Translate(Vector3 offset);

				const Vertex* GetEdgeVertex(int index);

				~Edge();
			private:
				Vertex* m_startVert;
				Vertex* m_endVert;
				SDL_Surface* m_SDLSurface;
			};

		}
	}
}

#endif
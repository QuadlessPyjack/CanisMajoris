/////////////////////////////////////////////////// 
//! \brief   Rasterizer - Canis Majoris Renderer
//!	\author  Bogdan Vitel
//! \details Rasterizer header
//! \date    19/12/2014
//! \todo 
//////////////////////////////////////////
#include<vector>

#include<Renderer/CoreUtils/Primitives/Mesh.h>
#include<Renderer/CoreUtils/Primitives/Triangle.h>
#include<Renderer/CoreUtils/Rasterizer/Rasterizer.h>

#include<Utils/MeshContainer.h>
#include<Utils/Constants.h>
#include<Utils/Validators.inl>

const int RASTERIZE_TRIANGLE_UP = 1;
const int RASTERIZE_TRIANGLE_DOWN = -1;
const int RASTERIZE_TRIANGLE_SPLIT = 0;
const int RASTERIZER_BREAK = -999;

namespace Core
{
	namespace Renderer
	{
		namespace CoreUtils
		{
			Rasterizer::Rasterizer(MeshContainer &meshPool, SDL_Surface* screen)
				: m_meshPool(&meshPool)
				, m_screen(screen)
			{}

			void Rasterizer::RasterizeScene()
			{
				std::vector<Triangle*> tri_vect;
				std::vector<const Vertex*> vert_vect;

				for (int i = 0; i < m_meshPool->length(); ++i)
				{
					tri_vect = m_meshPool->GetMesh(i)->GetTriangles();
					for (int j = 0; j < tri_vect.size(); ++j)
					{
						vert_vect = tri_vect[j]->GetVertices(); 
						fillHalfFlatTriangle(*vert_vect[0], *vert_vect[1], *vert_vect[2], RASTERIZE_TRIANGLE_DOWN, m_screen);
					}
				}
			}

			void Rasterizer::RasterizeMesh(Mesh &mesh)
			{

			}

			void Rasterizer::RasterizeTriangle(Triangle &tri)
			{

			}

			void Rasterizer::RasterizeByMeshID(std::string ID)
			{

			}

			void Rasterizer::RasterizeByTriangleID(std::string ID)
			{

			}

			void Rasterizer::fillHalfFlatTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3, int orientation, SDL_Surface* screen)
			{
				if (orientation != RASTERIZER_BREAK)
				{
					Vertex vA, vB, vC;

					float invslope1;
					float invslope2;

					if ((int)v1.y == (int)v2.y)
					{
						vA = v3;
						vB = v1;
						vC = v2;
					}
					else
						if ((int)v1.y == (int)v3.y)
						{
							vA = v2;
							vB = v1;
							vC = v3;

						}
						else
						{
							if (v1.y > v2.y && v1.y > v3.y)
							{
								vA = v1;
								vB = v2;
								vC = v3;
							}
							else if (v2.y > v1.y && v2.y > v3.y)
							{
								vA = v2;
								vB = v1;
								vC = v3;
							}
							else if (v3.y > v1.y && v3.y > v2.y)
							{
								vA = v3;
								vB = v1;
								vC = v2;
							}
						}

					orientation = RASTERIZER_BREAK;
					if (vA.y > vB.y && vA.y > vC.y && vB.y == vC.y)
						orientation = RASTERIZE_TRIANGLE_DOWN;
					else
						if (vA.y < vB.y && vA.y < vC.y && vB.y == vC.y)
							orientation = RASTERIZE_TRIANGLE_UP;
						/*else
							if (vB.y != vC.y)
								orientation = RASTERIZE_TRIANGLE_SPLIT;*/

					float lineX1 = vA.x;
					float lineX2 = vB.x;

					SDL_PixelFormat* fmt = screen->format;
					Uint32 rasterColour = SDL_MapRGB(fmt, 0, 255, 0);
					Uint32 rasterColour2 = SDL_MapRGB(fmt, 0, 0, 255);

					if (orientation == RASTERIZE_TRIANGLE_UP)
					{
						lineX2 = vA.x;
						invslope1 = (vB.x - vA.x) / (vB.y - vA.y);
						invslope2 = (vC.x - vA.x) / (vC.y - vA.y);

						for (float lineY = vA.y; lineY <= vB.y; lineY += RASTERIZER_GRANULARITY)
						{
							/*if (lineX1 <= 0)
							{
								lineX1 = 0.1f;
								break;
							}
							if (lineX2 <= 0)
							{
								lineX2 = 0.1f;
								break;
							}
							if (lineY <= 0)
							{
								lineY = 0.1f;
								break;
							}
							if (lineX1 >= 800)
							{
								lineX1 = 600;
								break;
							}
							if (lineX2 >= 800)
							{
								lineX2 = 600;
								break;
							}
							if (lineY >= 600)
							{
								lineY = 400;
								break;
							}*/
							if (ValidateScreenCoord(lineX1, 0) &&
								ValidateScreenCoord(lineX2, 0) &&
								ValidateScreenCoord(lineY, 1))
							{
								Draw_Line(screen, lineX1, lineY, lineX2, lineY, rasterColour);
							}
							//Draw_FillCircle(SDL_GetVideoSurface(), lineX2, lineY, 2, SDL_MapRGB(fmt, 255, 0, 255));

							lineX1 += invslope1;
							lineX2 += invslope2;
						}
					}
					else if (orientation == RASTERIZE_TRIANGLE_DOWN)
					{
						lineX2 = vA.x;
						invslope1 = (vA.x - vB.x) / (vA.y - vB.y);
						invslope2 = (vA.x - vC.x) / (vA.y - vC.y);

						for (float lineY = vA.y; lineY >= vB.y; lineY -= RASTERIZER_GRANULARITY)
						{
							/*if (lineX1 <= 0)
							{
								lineX1 = 0.1f;
								break;
							}
							if (lineX2 <= 0)
							{
								lineX2 = 0.1f;
								break;
							}
							if (lineY <= 0)
							{
								lineY = 0.1f;
								break;
							}
							if (lineX1 >= 800)
							{
								lineX1 = 600;
								break;
							}
							if (lineX2 >= 800)
							{
								lineX2 = 600;
								break;
							}
							if (lineY >= 600)
							{
								lineY = 400;
								break;
							}*/
							if (ValidateScreenCoord(lineX1, 0) &&
								ValidateScreenCoord(lineX2, 0) &&
								ValidateScreenCoord(lineY, 1))
							{
								Draw_Line(screen, lineX1, lineY, lineX2, lineY, rasterColour2);
							}
							//Draw_FillCircle(SDL_GetVideoSurface(), lineX1, lineY, 2, SDL_MapRGB(fmt, 0, 255, 255));
							lineX1 -= invslope1;
							lineX2 -= invslope2;
						}
					}
					else if (orientation == RASTERIZE_TRIANGLE_SPLIT)
					{
						Vertex v4;
						if (vC.x > vA.x)
							v4.x = vA.x + ((vB.y - vA.y) / (vC.y - vA.y)) * (vC.x - vA.x);
						else
							v4.x = vA.x + ((vB.y - vA.y) / (vC.y - vA.y)) * (vA.x - vC.x);

						if (vB.y > vC.y)
						{
							v4.y = vC.y;
							//vB = vC;
						}
						else
						{
							v4.y = vB.y;
						}
						//Draw_FillCircle(SDL_GetVideoSurface(), v4.x, v4.y, 7, SDL_MapRGB(fmt, 0, 150, 255));
						//Rasterizer::fillHalfFlatTriangle(vA, vB, v4, orientation, screen);
						//Rasterizer::fillHalfFlatTriangle(vB, v4, vC, orientation, screen);
					}
				}
			}
		
			Rasterizer::~Rasterizer()
			{
			
			}
		}
	}
}
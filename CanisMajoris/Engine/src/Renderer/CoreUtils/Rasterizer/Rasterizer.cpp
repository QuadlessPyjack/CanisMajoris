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
#include<Utils/Math/ConverterUtils.inl>

#include<SDL_video.h>

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

			Rasterizer::Rasterizer()
				: m_meshPool(nullptr)
				, m_screen(nullptr)
			{
			}

			void Rasterizer::RasterizeMesh(Mesh &mesh)
			{
				m_screen = Scene::GetViewport();
				std::vector<Triangle*> tri_vect;
				std::vector<const Vertex*> vert_vect;

					tri_vect = mesh.GetTriangles();
					for (int j = 0; j < tri_vect.size(); ++j)
					{
						Vector3 normal = tri_vect[j]->Normal();
						Vector3 cameraDirection = Scene::GetCamera()->Direction();
						normal.Normalize();

						if (cameraDirection.z == normal.z)
						{
							continue;
						}

						vert_vect = tri_vect[j]->GetVertices();
						
						// store all screen-space coordinates for our triangle's vertices
						Vector2 triangleScreenPoints[3] = { Vector2(0, 0), Vector2(0, 0), Vector2(0, 0) };
						Vector2 min(SCREEN_WIDTH, 0);
						Vector2 max(0, SCREEN_HEIGHT);

						/*int minIndex = -1;
						int maxIndex = -1;
						int thirdCornerIndex = -1;*/
						// convert to SS and identify the SS min and max bounds for the triangle
						for (int vxIndex = 0; vxIndex < vert_vect.size(); ++vxIndex)
						{
							triangleScreenPoints[vxIndex] = WorldToScreenCoords(vert_vect[vxIndex]->Location());
							
							ValidateAndCapScreenCoordinates(triangleScreenPoints[vxIndex]);
							
							if (triangleScreenPoints[vxIndex].x < min.x)
							{
								min.x = triangleScreenPoints[vxIndex].x;
							}
							// because the Y-axis is "upside-down" from our perspective, we flip the check on y-values
							if (triangleScreenPoints[vxIndex].y > min.y)
							{
								min.y = triangleScreenPoints[vxIndex].y;
							}
							
							if (triangleScreenPoints[vxIndex].x > max.x)
							{
								max.x = triangleScreenPoints[vxIndex].x;
							}

							// because the Y-axis is "upside-down" from our perspective, we flip the check on y-values
							if (triangleScreenPoints[vxIndex].y < max.y)
							{
								max.y = triangleScreenPoints[vxIndex].y;
							}
						}

						// guarantee that, no matter what, min and max are at opposite corners as per
						//
						//    __________Max
						//   |          |
						//   |          |
						//   |          |
						//   |          |
						//   |          |
						//   |__________|
						//  Min
						//
						//
						

						// we have to fit our triangle within rectangular bounds
						Bounds rasterBounds(min, max);
						
						// try to match triangle corners with bounds corners
						int* matchingPoints = matchTriangleOnBounds(triangleScreenPoints, rasterBounds);

						// three rectangle corners map directly to triangle corners => 90-degree angle triangle
						if (matchingPoints[4] == 3)
						{
							// its a 90-degree angle triangle, rasterize half the surface of our bounds

							int value = matchingPoints[0] * 1000 +
										matchingPoints[1] * 100  +
										matchingPoints[2] * 10   +
										matchingPoints[3];

							// 1110 = T && T
							if (value == 1110)
							{
								fillFlatTriangle(rasterBounds, true, true, m_screen);
								continue;
							}

							// 0111 = T && F

							if (value == 111)
							{
								fillFlatTriangle(rasterBounds, true, false, m_screen);
								continue;
							}

							// 1011 = F && F

							if (value == 1011)
							{
								fillFlatTriangle(rasterBounds, false, false, m_screen);
								continue;
							}

							// 1101 = F && T

							if (value == 1101)
							{
								fillFlatTriangle(rasterBounds, false, true, m_screen);
								continue;
							}

							continue;
						}

						// our triangle is not 90-degrees angled
						// which means that the bounds' corners that don't map with those of the triangle
						// form 90-degree triangles.
						// rasterize everything except for those surfaces
						if (matchingPoints[4] == 2)
						{
							int thirdCornerIndex = matchingPoints[5];
							if (thirdCornerIndex > 2 || thirdCornerIndex < 0)
							{
								continue;
							}

							Vector2 thirdCorner = triangleScreenPoints[thirdCornerIndex];

							fillTriangle(rasterBounds, thirdCorner, m_screen);
						}
					}
				//}
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

			void Rasterizer::fillFlatTriangle(Bounds rasterBounds, bool mirrorX, bool mirrorY, SDL_Surface* screen)
			{
				SDL_PixelFormat* fmt = screen->format;
				Uint32 rasterColour = SDL_MapRGB(fmt, 0, 255, 0);
				Uint32 rasterColour2 = SDL_MapRGB(fmt, 0, 0, 255);

				int numberOfLocks = 0;
				bool drawPixel = false;
				int skipInterval = 0;

				for (int yIndex = rasterBounds.maxCorner.y; yIndex < rasterBounds.minCorner.y; ++yIndex)
				{
					for (int xIndex = rasterBounds.upperCorner.x; xIndex < rasterBounds.maxCorner.x; ++xIndex)
					{
						if ((yIndex % 2 == 0) && xIndex % 3 == 0)
						{
							xIndex += skipInterval;
							continue;
						}

						if ((yIndex % 3 == 0) && xIndex % 2 == 0)
						{
							xIndex += skipInterval;
							continue;
						}

						Vector2 currentPoint(xIndex, yIndex);
						ValidateAndCapScreenCoordinates(currentPoint);

						if (SDL_MUSTLOCK(m_screen) != 0)
						{
							++numberOfLocks;
						}

						if (mirrorX == false && mirrorY == false)
						{
							//  _____
							// |    /
							// |   /
							// |  /
							// | /
							// |/

							if (slopeCompare(rasterBounds.maxCorner, currentPoint, rasterBounds.minCorner) < 0)
							{
								Draw_Pixel(m_screen, xIndex, yIndex, rasterColour);
								continue;
							}
						}

						if (mirrorX == false && mirrorY == true)
						{
							// rasterize lower half, which is basically the same thing, mirrored vertically
							// |\
							// | \
							// |  \
							// |   \
							// |    \
							// |_____\

							if (slopeCompare(rasterBounds.upperCorner, currentPoint, rasterBounds.lowerCorner) > 0)
							{
								Draw_Pixel(m_screen, xIndex, yIndex, rasterColour);
								continue;
							}
						}

						if (mirrorX == true && mirrorY == false)
						{
							// _____
							// \    |
							//  \   |
							//   \  |
							//    \ |
							//     \|
							//

							if (slopeCompare(rasterBounds.upperCorner, currentPoint, rasterBounds.lowerCorner) < 0)
							{
								Draw_Pixel(m_screen, xIndex, yIndex, rasterColour);
								continue;
							}
						}

						if (mirrorX == true && mirrorY == true)
						{
							//
							//      /|
							// 	   / |
							//    /  |
							//   /   |
							//  /    |
							// /_____|

							if (slopeCompare(rasterBounds.maxCorner, currentPoint, rasterBounds.minCorner) > 0)
							{
								Draw_Pixel(m_screen, xIndex, yIndex, rasterColour);
							}
						}
					}
				}

				//std::cout << "Number of locks called by SDL_draw on current triangle: " << numberOfLocks << std::endl;
			}

			void Rasterizer::fillTriangle(Bounds rasterBounds, Math::Vector2 thirdCorner, SDL_Surface* screen)
			{
				SDL_PixelFormat* fmt = screen->format;
				Uint32 rasterColour = SDL_MapRGB(fmt, 0, 255, 0);
				Uint32 rasterColour2 = SDL_MapRGB(fmt, 0, 0, 255);

				int numberOfLocks = 0;
				bool drawPixel = false;
				int skipInterval = 0;

				for (int yIndex = rasterBounds.maxCorner.y; yIndex < rasterBounds.minCorner.y; ++yIndex)
				{
					for (int xIndex = rasterBounds.upperCorner.x; xIndex < rasterBounds.maxCorner.x; ++xIndex)
					{
						if ((yIndex % 2 == 0) && xIndex % 3 == 0)
						{
							xIndex += skipInterval;
							continue;
						}

						if ((yIndex % 3 == 0) && xIndex % 2 == 0)
						{
							xIndex += skipInterval;
							continue;
						}

						Vector2 currentPoint(xIndex, yIndex);
						if (!ValidateScreenCoord(currentPoint))
						{
							continue;
						};

						if (SDL_MUSTLOCK(m_screen) != 0)
						{
							++numberOfLocks;
						}

						if (thirdCorner.x == rasterBounds.minCorner.x)
						{
							if ((slopeCompare(thirdCorner, currentPoint, rasterBounds.maxCorner) < 0 && currentPoint.y > thirdCorner.y) ||
								(slopeCompare(thirdCorner, currentPoint, rasterBounds.lowerCorner) < 0 && currentPoint.y < thirdCorner.y))
							{

								Draw_Pixel(m_screen, xIndex, yIndex, rasterColour);
								continue;
							}
						}

						if (thirdCorner.y == rasterBounds.maxCorner.y)
						{
							if ((slopeCompare(thirdCorner, currentPoint, rasterBounds.minCorner) > 0 && currentPoint.x < thirdCorner.x)||
								(slopeCompare(thirdCorner, currentPoint, rasterBounds.maxCorner) > 0 && currentPoint.x > thirdCorner.x))
							{

								Draw_Pixel(m_screen, xIndex, yIndex, rasterColour);
								continue;
							}
						}

						if (thirdCorner.x == rasterBounds.maxCorner.x)
						{
							if ((slopeCompare(thirdCorner, currentPoint, rasterBounds.upperCorner) < 0 && currentPoint.y > thirdCorner.y)||
								(slopeCompare(thirdCorner, currentPoint, rasterBounds.minCorner) < 0 && currentPoint.y < thirdCorner.y))
							{

								Draw_Pixel(m_screen, xIndex, yIndex, rasterColour);
								continue;
							}
						}

						if (thirdCorner.y == rasterBounds.minCorner.y)
						{
							if ((slopeCompare(thirdCorner, currentPoint, rasterBounds.upperCorner) > 0 && currentPoint.x < thirdCorner.x)||
								(slopeCompare(thirdCorner, currentPoint, rasterBounds.maxCorner) > 0 && currentPoint.x > thirdCorner.x))
							{

								Draw_Pixel(m_screen, xIndex, yIndex, rasterColour);
								continue;
							}

						}
						Vector2 boundsCenter = Vector2((rasterBounds.maxCorner.x - rasterBounds.minCorner.x) * 0.5, (rasterBounds.minCorner.y - rasterBounds.maxCorner.y) * 0.5);

						// see [desktop]\tri.PNG
						if (thirdCorner.y < boundsCenter.y && thirdCorner.x > boundsCenter.x)
						{
							float c1 = slopeCompare(rasterBounds.upperCorner, currentPoint, rasterBounds.lowerCorner);
							float c2 = slopeCompare(rasterBounds.upperCorner, currentPoint, thirdCorner);
							float c3 = slopeCompare(rasterBounds.lowerCorner, currentPoint, thirdCorner);

							if (c1 > 0 && c2 < 0 && c3 < 0)
							{
								Draw_Pixel(m_screen, xIndex, yIndex, rasterColour);
								continue;
							}
						}
					}
				}
			}

			//! Matches a series of triangle corners with the corners of a rectangular bounds structure
			//! @param trianglePoints The corners of a triangle
			//! @param rasterBounds  The bounds structure in which the triangle is placed in order to rasterize it
			//! @return An int[5] whereby the first 4 values represent the rectangle corners matching the triangle's
			//!         and [5] stores the number of matches (see ln. 277 for details)
			int* Rasterizer::matchTriangleOnBounds(Vector2* trianglePoints, Bounds& rasterBounds)
			{
				//! return type structure
				//! |  {0|1}  |   {0|1}   |  {0|1}  |   {0|1}   |     {0|1}      |     {int}      |
				//! |minCorner|lowerCorner|maxCorner|upperCorner|#matchingCorners|thirdCornerIndex|
				//!    0 = no match 1 = triangle corner matches this rectangle corner 
				int matchingPoints[6] = { 0, 0, 0, 0, 0, 0 };
				int matchingPointsFound = 0;
				int thirdCornerIndex = 3;

				for (int pointIndex = 0; pointIndex < 3; pointIndex++)
				{
					if (rasterBounds.minCorner.x == trianglePoints[pointIndex].x &&
						rasterBounds.minCorner.y == trianglePoints[pointIndex].y)
					{
						matchingPoints[0] = 1;
						matchingPointsFound++;

						thirdCornerIndex -= pointIndex;
						continue;
					}

					if (rasterBounds.lowerCorner.x == trianglePoints[pointIndex].x &&
						rasterBounds.lowerCorner.y == trianglePoints[pointIndex].y)
					{
						matchingPoints[1] = 1;
						matchingPointsFound++;

						thirdCornerIndex -= pointIndex;
						continue;
					}

					if (rasterBounds.maxCorner.x == trianglePoints[pointIndex].x &&
						rasterBounds.maxCorner.y == trianglePoints[pointIndex].y)
					{
						matchingPoints[2] = 1;
						matchingPointsFound++;

						thirdCornerIndex -= pointIndex;
						continue;
					}

					if (rasterBounds.upperCorner.x == trianglePoints[pointIndex].x &&
						rasterBounds.upperCorner.y == trianglePoints[pointIndex].y)
					{
						matchingPoints[3] = 1;
						matchingPointsFound++;

						thirdCornerIndex -= pointIndex;
						continue;
					}
				}

				matchingPoints[4] = matchingPointsFound;
				matchingPoints[5] = thirdCornerIndex;

				return matchingPoints;
			}

			float Rasterizer::slopeCompare(Math::Vector2 origin, Math::Vector2 point1, Math::Vector2 point2)
			{
				float m1, m2;

				m1 = abs((origin.y - point1.y) * (1 / (origin.x - point1.x)));
				m2 = abs((origin.y - point2.y) * (1 / (origin.x - point2.x)));

				return (m1 - m2);
			}

			Rasterizer::~Rasterizer()
			{
			
			}
		}
	}
}
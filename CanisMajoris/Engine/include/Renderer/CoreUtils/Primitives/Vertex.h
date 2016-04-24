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

namespace Core     {
namespace Renderer {
namespace CoreUtils{
 class CM_ENGINE_API Vertex
 {
  public:
  Vertex(float pozX, float pozY, float pozZ, int id = 0);
  Vertex(); //!< \todo Should probably find a way to restrict this
  explicit Vertex(Vector3 v3, int id = 0);
  explicit Vertex(float coordinates[3], int id = 0);

  void SetOwner(std::string ownerName);
  const std::string GetOwner();

  void Draw();
  void ResetTransform();
  bool IsDirty() const;

  int id() const;
  void SetID(int vertexID);
  const Vector3 &Location();
  void SetLocation(Vector3 location);
  void Translate(Vector3 offset);
  void Scale(const Vector3& centre, float scaleFactor);
  void Rotate(const Vector3& centre, Vector3 amount);

  ~Vertex();

  float x;
  float y;
  float z;

  private:
  int m_id;
  bool m_dirtyFlag;
  SDL_Surface* m_SDLSurface;
  std::string m_meshOwnerName;
  Vector3 m_v3;
  Vector3 m_wsTransform;
 };
} // CoreUtils
} // Renderer
} // Core

#endif // VERTEX_H
#ifndef OBJECT_H
#define OBJECT_H
////////////////////////////////////////// 
//! \brief   Scene Object Entity
//!	\author  Bogdan Vitel
//! \details Object virtual class header
//! \date    28/01/2016
//! \todo Group duplicate base methods into a virtual class
//////////////////////////////////////////

#include <Utils/Math/Vector3.h>
#include <EngineDllExport.h>

namespace Core
{

	//forward declarations
	namespace Renderer  {
	namespace CoreUtils {
			class Mesh;
	}
	}

	namespace Game
	{
		namespace Entities
		{
			class CM_ENGINE_API Object
			{
			public:
				Object();
				Object(Renderer::CoreUtils::Mesh *mesh, Vector3 location);
				virtual ~Object();
				virtual void Draw();

				virtual Vector3 Location() const;
				virtual void  SetLocation(Vector3 location);
				virtual Renderer::CoreUtils::Mesh &GetMesh();
				virtual void SetMesh(Renderer::CoreUtils::Mesh *mesh);
				
				virtual void Translate(Vector3 offset);
				virtual void Scale(Vector3 centre, float scaleFactor);
				virtual void Scale(float scaleFactor);
				
				virtual void Rotate(Vector3 centre, Vector3 amount);
				virtual void Rotate(Vector3 amount);

			private:
				void updateMeshTransform();
				Renderer::CoreUtils::Mesh *m_mesh;
				Vector3 m_location;
			};
		}
	}
}
#endif // OBJECT_H
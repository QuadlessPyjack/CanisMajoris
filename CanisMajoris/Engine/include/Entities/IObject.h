#ifndef IOBJECT_H
#define IOBJECT_H
////////////////////////////////////////// 
//! \brief   Scene Object Entity
//!	\author  Bogdan Vitel
//! \details Object virtual class header
//! \date    28/01/2016
//! \todo Group duplicate base methods into a virtual class
//////////////////////////////////////////

//forward declarations
class Vector3;

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
			class IObject
			{
			public:
				IObject();
				virtual ~IObject() = 0;
				virtual void Draw() = 0;

				virtual const Vector3 Location() = 0;
				virtual void  SetLocation(Vector3 location) = 0;
				virtual Renderer::CoreUtils::Mesh &GetMesh() = 0;
				
				virtual void Translate(Vector3 offset) = 0;
				virtual void Scale(Vector3 centre, float scaleFactor) = 0;
				virtual void Scale(float scaleFactor) = 0;
				
				virtual void Rotate(Vector3 centre, Vector3 amount) = 0;
				virtual void Rotate(Vector3 amount) = 0;


			};
		}
	}
}
#endif // STATIC_OBJECT_H
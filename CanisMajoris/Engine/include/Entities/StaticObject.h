#ifndef STATIC_OBJECT_H
#define STATIC_OBJECT_H
////////////////////////////////////////// 
//! \brief   Static Scene Object Entity
//!	\author  Bogdan Vitel
//! \details Static Object class header
//! \date    28/01/2016
//! \todo Group duplicate base methods into a virtual class
//////////////////////////////////////////

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
			class StaticObject
			{
			public:
				StaticObject();

			private:
				Renderer::CoreUtils::Mesh *m_mesh;
			};
		}
	}
}
#endif // STATIC_OBJECT_H
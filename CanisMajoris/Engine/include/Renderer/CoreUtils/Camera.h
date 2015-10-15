#ifndef CAMERA_H
#define CAMERA_H
////////////////////////////////////////// 
//! \brief   Camera - Canis Majoris Renderer
//!	\author  Bogdan Vitel
//! \details Camera class header
//! \date    28/11/2014
//! \todo To be determined
//////////////////////////////////////////
#include<EngineDllExport.h>

#include<Utils/Math/Vector2.h>
#include<Utils/Math/Vector3.h>

namespace Core
{
	namespace Renderer
	{
		namespace CoreUtils
		{
			class CM_ENGINE_API Camera
			{
			public:
				Camera(Vector3 pozition );
				~Camera();
				const Vector3 Location() { return m_location; };
				void Move(Vector3 amount) {
				m_location.x = m_location.x + amount.x;
				m_location.y = m_location.y + amount.y;
				m_location.z = m_location.z + amount.z;
				};

			private:
				Vector3 m_location;
			};
		}
	}
}
#endif
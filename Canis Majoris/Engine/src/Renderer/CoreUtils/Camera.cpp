////////////////////////////////////////// 
//! \brief   Camera - Canis Majoris Renderer
//!	\author  Bogdan Vitel
//! \details Camera class src
//! \date    28/11/2014
//! \todo To be determined
//////////////////////////////////////////
#include<Renderer/CoreUtils/Camera.h>

#include<Utils/Math/ConverterUtils.inl>

namespace Core
{
	namespace Renderer
	{
		namespace CoreUtils
		{
			Camera::Camera(Vector3 pozition) : m_location(pozition)
			{};

			Camera::~Camera()
			{};
		}
	}
}
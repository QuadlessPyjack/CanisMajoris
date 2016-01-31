/////////////////////////////////////////////////////////////////////// 
//! \brief   UITextLabel - Canis Majoris UI
//! \author  Bogdan Vitel
//! \details UI Label container for 3D text
//! \date    31/01/2016
//! \todo    
//////////////////////////////////////////////////

#include<UI/UITextLabel.h>

namespace Renderer {
namespace UI       {
	namespace
	{
		const Vector3 defaultMinBound(340.0f, 390.0f, 0.0f);
		const Vector3 defaultMaxBound(400.0f, 400.0f, 0.0f);
	}

	UITextLabel::UITextLabel()
		: m_labelBounds(defaultMinBound, defaultMaxBound)
		, m_text("[NULL]")
		, m_UIText()
	{
		
	}

	UITextLabel::UITextLabel(Math::Vector2 position, float width, float height)
	{
		
	}

	UITextLabel::UITextLabel(Bounds bounds)
	{
		
	}
} // namespace UI
} // namespace Renderer
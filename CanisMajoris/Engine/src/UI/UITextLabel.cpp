/////////////////////////////////////////////////////////////////////// 
//! \brief   UITextLabel - Canis Majoris UI
//! \author  Bogdan Vitel
//! \details UI Label container for 3D text
//! \date    31/01/2016
//! \todo    
//////////////////////////////////////////////////

#include<UI/UITextLabel.h>
#include <list>
#include <Renderer/CoreUtils/Primitives/Mesh.h>

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

	void UITextLabel::setStringToUIText(std::string text)
	{
		//std::list<Core::Game::Entities::UIObject> font = FontLoader::GetInstance()::GetFont();
		std::list<Core::Game::Entities::UIObject> font;
		std::list<Core::Game::Entities::UIObject>::iterator it;

		for (int index = 0; index < text.size(); ++index)
		{
			for (it = font.begin(); it != font.end(); ++it)
			{
				if ((*it).GetMesh().GetID()[0] == text[index])
				{
					m_UIText.push_back(*it);
					break;
				}
			}
		}
	}
} // namespace UI
} // namespace Renderer
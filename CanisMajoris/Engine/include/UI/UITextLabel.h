#ifndef UITEXTLABEL_H
#define UITEXTLABEL_H
/////////////////////////////////////////////////////////////////////// 
//! \brief   UITextLabel - Canis Majoris UI
//! \author  Bogdan Vitel
//! \details UI Label container for 3D text
//! \date    31/01/2016
//! \todo    
//////////////////////////////////////////////////
#include<EngineDllExport.h>
#include <string>
#include <vector>
#include <Entities/UIObject.h>

// forward declarations
namespace Math 
{
	class Vector2;
	class Vector3;
}

namespace Renderer {
namespace UI       {

class UITextLabel
{
public:
	UITextLabel();
	UITextLabel(Math::Vector2 position, float width = 0.0f, float height = 0.0f);
	UITextLabel(Bounds bounds);

private:

	void setStringToUIText(std::string text);

	Bounds m_labelBounds;
	std::string m_text;
	std::vector<Core::Game::Entities::UIObject> m_UIText;
};

} // namespace UI
} // namespace Renderer


#endif //UITEXTLABEL_H
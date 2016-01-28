#ifndef UITEXTLABEL_H
#define UITEXTLABEL_H
/////////////////////////////////////////////////////////////////////// 
//! \brief   Scene - Canis Majoris Renderer
//! \author  Bogdan Vitel
//! \details Container Header for all common, vital, Scene Components
//! \date    14/02/2015
//! \todo    17/02/2015 - Created Singleton Class, added methods for Camera and SDL_Surface
//////////////////////////////////////////////////
#include<EngineDllExport.h>

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
};

} // namespace UI
} // namespace Renderer


#endif //UITEXTLABEL_H
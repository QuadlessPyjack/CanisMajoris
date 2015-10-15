#ifndef SCENE_H
#define SCENE_H
/////////////////////////////////////////////////////////////////////// 
//! \brief   Scene - Canis Majoris Renderer
//! \author  Bogdan Vitel
//! \details Container Header for all common, vital, Scene Components
//! \date    14/02/2015
//! \todo    17/02/2015 - Created Singleton Class, added methods for Camera and SDL_Surface
//////////////////////////////////////////////////
#include<EngineDllExport.h>

struct SDL_Surface;

namespace Core      {
namespace Renderer  {
namespace CoreUtils {
 class Camera;

 class CM_ENGINE_API Scene
 {
 public:
 ~Scene();

 static void InitScene(Camera *camera);
 static Scene &GetInstance();

 static Camera *GetCamera();
 static SDL_Surface *GetViewport();

 private:
 Scene();

 static Scene *m_Scene;
 SDL_Surface *m_SceneViewport;
 Camera *m_MainCamera;
 };

} // CoreUtils
} // Renderer
} // Core

#endif // SCENE_H
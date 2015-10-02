/////////////////////////////////////////////////////////////////////// 
//! \brief   Scene - Canis Majoris Renderer
//! \author  Bogdan Vitel
//! \details Container Source for all common, vital, Scene Components
//! \date    14/02/2015
//! \todo    17/02/2015 - Created Singleton Class, added methods for Camera and SDL_Surface
//////////////////////////////////////////////////
#include<cassert>
#include<SDL.h>

#include<iostream>

#include<Renderer/CoreUtils/Scene.h>
#include<Renderer/CoreUtils/Camera.h>

namespace Core      {
namespace Renderer  {
namespace CoreUtils	{
 Scene *Scene::m_Scene = nullptr;
 void Scene::InitScene(Camera *camera)
 {
 	if (m_Scene)
 	{
 		m_Scene->m_MainCamera = camera;
 		std::cout << "InitScene m_Scene: " << m_Scene << std::endl;
 	}
 };
 Scene &Scene::GetInstance()
 {
 	if (m_Scene == nullptr)
 	{
 		m_Scene = new Scene();
 		std::cout << "GetInstance m_Scene: " << m_Scene << std::endl;
 		return *m_Scene;
 	}
 	return *m_Scene;
 };
 
 Camera *Scene::GetCamera()
 {
 	assert(m_Scene);
 	return m_Scene->m_MainCamera;
 }
 
 SDL_Surface *Scene::GetViewport()
 {
 	assert(m_Scene);
 	return m_Scene->m_SceneViewport;
 }
 
 Scene::Scene()
 {
 	m_SceneViewport = SDL_GetVideoSurface();
 };
 Scene::~Scene()
 {
 	delete m_Scene;
 	m_Scene = nullptr;
 };	
} // CoreUtils
} // Renderer
} // Core
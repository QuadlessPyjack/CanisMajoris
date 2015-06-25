#ifndef MESHCONTAINER_H
#define MESHCONTAINER_H
////////////////////////////////////////// 
//! \brief   MeshContainer - Canis Majoris Math Utils
//!	\author  Bogdan Vitel
//! \details Mesh Storage and Manipulation Class Header
//!			 Glorified wrapper around std::vector
//! \date    14/11/2014
//! \todo
//////////////////////////////////////////
#include<EngineDllExport.h>

#include<iostream>
#include<string>
#include<algorithm>

#include<Renderer/CoreUtils/Primitives/Mesh.h>


class CM_ENGINE_API MeshContainer
{
public:
 MeshContainer();
 
 bool Exists(Core::Renderer::CoreUtils::Mesh* pMesh);
 bool Exists(std::string ID);
 
 Core::Renderer::CoreUtils::Mesh* GetMesh(std::string meshID);
 
 Core::Renderer::CoreUtils::Mesh* MeshContainer::GetMesh(int meshIndex);
 
 //wrapper methods follow
 void AddMesh(Core::Renderer::CoreUtils::Mesh* mesh);
 void RemoveMesh(Core::Renderer::CoreUtils::Mesh* mesh);
 int length();
 
 void clear();
 
 ~MeshContainer();
 
private:
 std::vector<Core::Renderer::CoreUtils::Mesh*> m_meshContainer;
};

#endif //MESHCONTAINER_H
#ifndef IO_L3D_H
#define IO_L3D_H
////////////////////////////////////////// 
//! \brief   IO_L3D_H - Canis Majoris Renderer
//! \author  Bogdan Vitel
//! \details L3D File Loader Header
//! \date    25/04/2016
//! \todo 
//////////////////////////////////////////
#include<EngineDllExport.h>
#include <string>
#include <Renderer/CoreUtils/Primitives/Vertex.h>
#include <Renderer/CoreUtils/Primitives/Edge.h>

#include <msclr\auto_gcroot.h>

#using <mscorlib.dll>
#using <lupus3D.dll>

using namespace System;

class MeshContainer;


namespace Core {
namespace IO   {
namespace L3D  {

			ref class /*CM_ENGINE_API*/ ModelCLR
			{
			public:
				ModelCLR();

				ModelCLR(String^ filePath);

				void Load(String^ filePath);
				void Save(String^ filePath);
				void AddMesh(Lupus3D::FileInfo::MeshFile^ meshFile);
				

				bool IsValid();

				array<Lupus3D::FileInfo::MeshFile^>^ GetMeshFiles();

			private:
				String^ m_filename;
				array<Lupus3D::FileInfo::MeshFile^>^ m_meshes;

				Lupus3D::Model^ m_model;

			};
}
}
}

#endif // IO_L3D_H
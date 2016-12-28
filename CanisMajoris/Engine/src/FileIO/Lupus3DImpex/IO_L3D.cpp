////////////////////////////////////////// 
//! \brief   IO_L3D - Canis Majoris Renderer
//! \author	 Bogdan Vitel
//! \details L3D File Loader src
//! \date	 25/04/2016
//! \todo Create unified load method wrapper for Vertex, Edge and Triangle data
//!	\todo Read Mesh Object names and register them in vertices, also spawn shell mesh objects
//////////////////////////////////////////

#include <FileIO/Lupus3DImpex/IO_L3D.h>

#using <mscorlib.dll>
#using <lupus3D.dll>

namespace Core {
namespace IO   {
namespace L3D  {

	using namespace Lupus3D;
	using namespace Lupus3D::FileInfo;

	ModelCLR::ModelCLR()
	{
		m_model = gcnew Model();
	}

	ModelCLR::ModelCLR(String^ filePath)
	{

	}

	void ModelCLR::AddMesh(MeshFile^ meshFile)
	{
		m_model->AddMesh(meshFile);
	}

	void ModelCLR::Load(String^ filePath)
	{
		m_model->LoadFile(filePath);
	}

	void ModelCLR::Save(String^ filePath)
	{
		m_model->SaveFile(filePath);
	}

	bool ModelCLR::IsValid()
	{
		return m_model->isValid();
	}

	array<MeshFile^>^ ModelCLR::GetMeshFiles()
	{
		if (m_model->isValid())
		{
			return m_model->ExtractMeshData();
		}

		return gcnew array<MeshFile^>(0);
	}

} // namespace L3D
} // namespace IO
} // namespace Core
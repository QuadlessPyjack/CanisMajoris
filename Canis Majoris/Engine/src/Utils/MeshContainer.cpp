////////////////////////////////////////// 
//! \brief   MeshContainer - Canis Majoris Math Utils
//!	\author  Bogdan Vitel
//! \details Mesh Storage and Manipulation Class src
//!			 Glorified wrapper around std::vector
//! \date    14/11/2014
//! \todo 
//////////////////////////////////////////

#include<Utils/MeshContainer.h>

MeshContainer::MeshContainer()
{};

bool MeshContainer::Exists(Core::Renderer::CoreUtils::Mesh* pMesh)
{
	if (!m_meshContainer.empty())
	{
		for (int i = 0; i < m_meshContainer.size(); ++i)
		{
			if (m_meshContainer[i] == pMesh)
				return true;
		}
	}

	return false;
};

bool MeshContainer::Exists(std::string ID)
{
	if (!m_meshContainer.empty())
	{
		for (int i = 0; i < m_meshContainer.size(); ++i)
		{
			if (m_meshContainer[i]->GetID() == ID)
				return true;
		}
	}

	return false;
};

Core::Renderer::CoreUtils::Mesh* MeshContainer::GetMesh(std::string meshID)
{
	if (!m_meshContainer.empty())
	{
		for (int i = 0; i < m_meshContainer.size(); ++i)
		{
			if (m_meshContainer[i]->GetID() == meshID)
				return m_meshContainer[i];
		}
	}

	return new Core::Renderer::CoreUtils::Mesh("NULL");
};

Core::Renderer::CoreUtils::Mesh* MeshContainer::GetMesh(int meshIndex)
{
	return m_meshContainer[meshIndex];
}

//wrapper methods follow
void MeshContainer::AddMesh(Core::Renderer::CoreUtils::Mesh* mesh)
{
	m_meshContainer.push_back(mesh);
};

void MeshContainer::RemoveMesh(Core::Renderer::CoreUtils::Mesh* mesh)
{
	m_meshContainer.erase(
							std::remove(m_meshContainer.begin(), 
										m_meshContainer.end(),
										mesh
									   ),
							m_meshContainer.end()
						);
};

int MeshContainer::length()
{
	return m_meshContainer.size();
};

void MeshContainer::clear()
{
	for (int i = 0; i < m_meshContainer.size(); ++i)
	{
		m_meshContainer[i] = nullptr;
		delete m_meshContainer[i];
	}

	m_meshContainer.clear();
};

MeshContainer::~MeshContainer()
{
	clear();
};
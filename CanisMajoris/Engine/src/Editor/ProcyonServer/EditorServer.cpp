//////////////////////////////////////////////////////// 
//! \brief   Editor - Codename Procyon
//!	\author  Bogdan Vitel
//! \details Editor Server Manager for Shared Memory
//! \date    11/03/2015
//! \todo To be determined
//////////////////////////////////////////
#include<boost/interprocess/windows_shared_memory.hpp>
#include<boost/interprocess/mapped_region.hpp>

#include<Editor/ProcyonServer/EditorServer.h>

#define _CRT_SECURE_NO_WARNINGS

namespace Editor
{
	ProcyonServer *ProcyonServer::m_server = nullptr;
	boost::interprocess::windows_shared_memory ProcyonServer::m_shm 
	=boost::interprocess::windows_shared_memory();
	boost::interprocess::mapped_region ProcyonServer::m_region
	=boost::interprocess::mapped_region();

	ProcyonServer::ProcyonServer()
	:canWriteToMemory(false)
	{
		canWriteToMemory = false;
	}

	ProcyonServer::~ProcyonServer()
	{
		delete m_server;
		m_server = nullptr;
	}

	bool ProcyonServer::InitializeEditorServer()
	{
		if (ProcyonServer::m_server)
		{
			using namespace boost::interprocess;
			ProcyonServer::m_shm
			=windows_shared_memory(create_only, "DBG_LOG_MEM", read_write, 1024);
			ProcyonServer::m_region
			=mapped_region(m_shm, read_write);

			std::memset(m_region.get_address(), '0', m_region.get_size());
			
			canWriteToMemory = true;
			return true;
		}

		return false;
	}

	ProcyonServer &ProcyonServer::GetInstance()
	{
		if (m_server == nullptr)
		{
			m_server = new ProcyonServer();
			m_server->canWriteToMemory = false;
		}

		return *m_server;
	}

	void ProcyonServer::LogInfo(const std::string text)
	{
		if (canWriteToMemory)
		{
			char msg[100];
			strcpy_s(msg, text.c_str());
			int size = strlen(text.c_str());
			std::memcpy(m_region.get_address(), msg, size);
		}
	}


}
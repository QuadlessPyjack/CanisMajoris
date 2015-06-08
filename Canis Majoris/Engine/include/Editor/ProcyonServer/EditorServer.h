#ifndef EDITOR_SERVER_H
#define EDITOR_SERVER_H
//////////////////////////////////////////////////////// 
//! \brief   Editor - Codename Procyon
//!	\author  Bogdan Vitel
//! \details Editor Server Manager for Shared Memory
//! \date    11/03/2015
//! \todo To be determined
//////////////////////////////////////////

#include<EngineDllExport.h>

//forward declarations
namespace boost
{
	namespace interprocess
	{
		class windows_shared_memory;
		class mapped_region;
	}
}

namespace Editor
{
	class CM_ENGINE_API ProcyonServer
	{
	public:
		static ProcyonServer &GetInstance();
		bool InitializeEditorServer();
		void LogInfo(const std::string text);

		~ProcyonServer();
	private:
		ProcyonServer();
		static ProcyonServer *m_server;
		static boost::interprocess::windows_shared_memory m_shm;
		static boost::interprocess::mapped_region m_region;
		bool canWriteToMemory = false;
	};
}

#endif
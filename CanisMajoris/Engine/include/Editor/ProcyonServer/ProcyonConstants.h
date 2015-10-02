#ifndef PROCYON_CONSTANTS_H
#define PROCYON_CONSTANTS_H

////////////////////////////////////////// 
//! \details Constants
//  Bogdan Vitel - Procyon Editor
//	Constants and other utility values
//  Created: 11/03/2015
//! \todo 
//////////////////////////////////////////

//! Shared memory configuration constants
static const char SHARED_MEMORY_ID[] = "PROCYON_COMM_DATA";
static const int  SHARED_MEMORY_BUFFER_SIZE = 1024;

//! \brief Shared memory reserved data

//! The following values have special meaning
//! for Procyon and are restricted.
//! DO NOT USE THEM OUTSIDE THEIR PREDETERMINED CONTEXT!

//! used to signal Procyon that no new data is being sent
static const char SHARED_MEMORY_CLEAR[] = "0";

//! used to signal Procyon that it should kill itself gracefully
static const char SHARED_MEMORY_SIGKILL[] = "SIGKILL";

//! Log text prefixes
//! \todo See if error lines can be made red. [low priority]
static const char LOG_INFO[] = "[INFO] ";
static const char LOG_WARNING[] = "[/!\] ";
static const char LOG_ERROR[] = "[ERROR] ";


#endif
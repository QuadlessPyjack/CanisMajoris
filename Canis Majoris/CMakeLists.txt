#######################################################
# CMake Projects Generator for Canis Majoris Engine and Utils
# Author: Bogdan Vitel
# Date: 21/04/2015
#######################################################

cmake_minimum_required (2.6)
string  (TIMESTAMP START_TIME)
project (CanisMajoris)


# Global Config Flags
set_property (global property USE_FOLDERS ON)

# Global Variables
## CMake Bin Directories
set (ENGINE_BIN_DIR "../bin")
set (EDITOR_BIN_DIR "../bin/Editor")
set (TEST_FRAMEWORK_BIN_DIR "../bin/TestFramework")

## Source Directories
set (ENGINE_SOURCE_DIR "Engine/src")
set (GAME_SOURCE_DIR "Game/src")
set (EDITOR_SOURCE_DIR "Procyon/src")
set (TEST_FRAMEWORK_SOURCE_DIR "TestFramework/src")

## Include Directories
set (ENGINE_INC_DIR "Engine/include")
set (GAME_INC_DIR "Game/include")
set (EDITOR_INC_DIR "Procyon/include")
set (TEST_FRAMEWORK_INC_DIR "TestFramework/include")

# Library Output Directory
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${ENGINE_BIN_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ENGINE_BIN_DIR})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ENGINE_BIN_DIR})

## Libraries Location
if (WIN32)
set (LIBS_DIR "Z:")
elseif (UNIX)
set (LIBS_DIR "/z")
endif ()

# Projects folders
add_subdirectory(Engine ${ENGINE_BIN_DIR})
add_subdirectory(Game ${ENGINE_BIN_DIR})
add_subdirectory(Procyon ${EDITOR_BIN_DIR})
add_subdirectory(TestFramework ${TEST_FRAMEWORK_BIN_DIR})



string  (TIMESTAMP END_TIME)
message (STATUS "CMake Configuration started at: " ${START_TIME})
message (STATUS "Setting Libraries Directory to: " ${LIBS_DIR})
message (STATUS "CMake Configuration finished at: " ${END_TIME})
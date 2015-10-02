################################
# CMake Project Generator
# Project: Canis Majoris Engine
# Author: Bogdan Vitel
# Date: 22/04/2015
#################################


project(Engine)


# Engine Source Files
set (ENGINE_SRC
${ENGINE_SOURCE_DIR}/Editor/ProcyonServer/EditorServer.cpp
${ENGINE_SOURCE_DIR}/FileIO/OBJImpex/Reader/IO_OBJLoader.cpp
#${ENGINE_SOURCE_DIR}/FileIO/OBJImpex/Writer/IO_OBJExporter.cpp
${ENGINE_SOURCE_DIR}/Renderer/CoreUtils/Camera.cpp
${ENGINE_SOURCE_DIR}/Renderer/CoreUtils/Scene.cpp

${ENGINE_SOURCE_DIR}/Renderer/CoreUtils/Primitives/Vertex.cpp
${ENGINE_SOURCE_DIR}/Renderer/CoreUtils/Primitives/Edge.cpp
${ENGINE_SOURCE_DIR}/Renderer/CoreUtils/Primitives/Triangle.cpp
${ENGINE_SOURCE_DIR}/Renderer/CoreUtils/Primitives/Mesh.cpp

${ENGINE_SOURCE_DIR}/Rasterizer/Rasterizer.cpp

#${ENGINE_SOURCE_DIR}/ScriptAPI/

${ENGINE_SOURCE_DIR}/Utils/MeshContainer.cpp
${ENGINE_SOURCE_DIR}/Utils/Math/Vector2.cpp
${ENGINE_SOURCE_DIR}/Utils/Math/Vector3.cpp
)

# Platform Specific Stuff
##

add_library (Engine SHARED ${ENGINE_SRC})

link_directories( 
${LIBS_DIR}
)

include_directories(
${LIBS_DIR}
)

find_library (SDL_LIB
NAMES SDL-1.2.15 SDL
PATHS ${LIBS_DIR}
)

find_library (SDL_DRAW_LIB
NAMES SDL_draw-1.2.13 SDL_draw
PATHS ${LIBS_DIR}
)

find_library (BOOST_LIB
NAMES boost-1.57.0 boost
PATHS ${LIBS_DIR}
)

target_link_libraries (Engine SDL_LIB SDL_DRAW_LIB BOOST_LIB)
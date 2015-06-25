#ifndef CONSTANTS_H
#define CONSTANTS_H

////////////////////////////////////////// 
//! \details Constants
//  Bogdan Vitel - Canis Majoris Renderer
//	Constants and other utility values
//  Created: 11/11/2014
//! \todo 
//////////////////////////////////////////

static int SCREEN_WIDTH = 800;
static int SCREEN_HEIGHT = 600;

//Used by main.cpp
static int VERTEX_COUNT;
static int EDGE_COUNT;

const char* const TEST_MODEL_FILENAME = "../DBG_MAP.obj";//"DBG_ALLIANCE.obj";//"DBG_MESH.obj";//"DBG_CUBE.obj";//"CanisOBJTest3.obj";

//Used by rasterizer
static const float RASTERIZER_GRANULARITY = 1.0f;

//Used by IO_OBJLoader.cpp
const int   TEMP_OFFSETX = 0;
const int   TEMP_OFFSETY = 0;
const float AMPLIFICATION_FACTOR = 1.2f;

//Used by Camera
const float CAM_SPEED = 10.5f;

//Used by PhysicsManager
const Uint32 PHYS_TICK = 100;

//Used by Engine
const Uint32 ENGINE_TICK = 50;

#endif // CONSTANTS_H
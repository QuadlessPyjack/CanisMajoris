# CanisMajoris
##3D and Game Engine built from scratch using only SDL

### About

This project was born out of 1 part stubborness, 1 part OpenGL frustrations and 1 part unadulterated madness.
It also served and continues to serve as a multipurpose research project into whatever areas I fancy.
The end result should be a retro style 3D wireframe game - possibly a TIE-fighter like flight sim.

### Features

1. Currently implemented:
 * OBJ model file loading
 * 3D Wireframe Perspective rendering
 * Camera and Scene support (navigate via arrow keys and W,S for height, Q,E for rotation)
 * Geometry transform, scaling and rotation
 
2. Under development:
 * Procyon Level Editor and Remote Debugging Console
 * Windows 98 Game Engine Port for all those retro gaming feels (Procyon currently not planned for porting)
 * Scalable, robust Event System Handler with aggressive performance behaviours 
  (targeted event subscriptions and broadcast, priority handling, aggressive message culling)
 * Physics System
 
 ### Setup
 
 *CanisMajoris/SetMeUpScotty.bat* should configure your environment and run the Visual Studio 2014 solution.
 *CanisMajoris* contains all the source code for CanisMajoris as well as Procyon.
 *Auxiliaries* contains all sorts of 3rd party libraries such as boost, SDL, SDLdraw etc.

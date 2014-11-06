// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 7 constants.h v1.0

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <stdlib.h>     
#include <time.h>  

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------

// window
const char CLASS_NAME[] = "Village Hero";
const char GAME_TITLE[] = "Village Hero";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH =  800;               // width of game in pixels
const UINT GAME_HEIGHT = 600;               // height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations

// graphic images
const char NEBULA_IMAGE[] =   "pictures\\forest path.png";     // photo source NASA/courtesy of nasaimages.org 
const char SHIP_IMAGE[] = "pictures\\defender_sheet.png";  // game textures
const char SNAKE_IMAGE[] = "pictures\\snake_sheet.png";
const char SPIDER_IMAGE[] = "pictures\\spider_sheet.png";
const char ARMADILLO_IMAGE[] = "pictures\\armadillo_sheet.png";
const char HEALTHBAR[] = "pictures\\health_sheet.png";
const char MISSILE_IMAGE[] = "pictures\\missile_sheet.png";
// audio files required by audio.cpp
// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[]  = "audio\\Win\\Wave Bank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\Sound Bank.xsb";

// audio cues
const char HIT[]   = "hit";
const char SHOOT[] = "shoot";
const char DAMAGE[] = "damage";
const char WIN[] = "win";
const char LOSE[] = "lose";
const char BACKGROUND[] = "background";

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key

enum WEAPON {TORPEDO, SHIP, PLANET};

#endif

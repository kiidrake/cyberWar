// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 spacewar.h v1.0

#ifndef _SPACEWAR_H             // Prevent multiple definitions if this 
#define _SPACEWAR_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "baseTurret.h"
#include "enemySpawner.h"
#include "coreEnemy.h"
#include "ship.h"
#include "missile.h"
#include "healthbar.h"
#include "snake.h"
#include "armadillo.h"
#include "spider.h"
#include "textDX.h"
#include <sstream>
#include <string>

//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:
    // game items
    TextureManager nebulaTexture;   // nebula texture
	TextureManager snakeTexture;
    TextureManager gameTextures;    // game texture
	TextureManager armadilloTexture;
	TextureManager spiderTexture;
	TextureManager healthTexture;
	TextureManager missileTexture;
	TextureManager turretBaseTexture;
	TextureManager turretTextureOne;
    Ship    ship1;           // spaceships
	Missile missiles[50];
	BaseTurret baseTurrets[5];
	Image spawners[4];
	coreEnemy enemies[100];
	Missile turretMissiles1[50];
	

	Health health;
    Image   nebula;         // backdrop image
	Image turretBases[5];
	int colCounter;
	int missileIndex;
	int turretMissileIndex1;
	int spawnLoc;
	VECTOR2* fireVector;
	VECTOR2* forward;
	bool fired;
	bool turretFired1;
	int score;
	
	float S1WaveTimer;
	float S2WaveTimer;
	float S3WaveTimer;
	float S4WaveTimer;
	float gameTimer;
	float increaseTime;

	bool gamePlaying;
	bool preGame;
	float preGameTimer;
	TextDX *output;
	TextDX *outputHL;
	std::string outString;
	std::string finalString;
	std::string swarmString;
	std::string introString1;
	std::string introString2;
	std::string introString3;
public:
    // Constructor
    Spacewar();

    // Destructor
    virtual ~Spacewar();
	float angle;
    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();
};

#endif

// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 spacewar.h v1.0

#ifndef _SPACEWAR_H             // Prevent multiple definitions if this 
#define _SPACEWAR_H             // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h";
#include "sniperTurret.h"
#include "triTurret.h"
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
#include "core.h"
#include "walsh.h"
#include <sstream>
#include <string>

//=============================================================================
// This class is the core of the game
//=============================================================================
class Spacewar : public Game
{
private:
    // game items
    TextureManager nebulaTexture;
	TextureManager spawnerTexture;
	TextureManager enemyTexture;
	TextureManager snakeTexture;
    TextureManager gameTextures;    // game texture
	TextureManager armadilloTexture;
	TextureManager spiderTexture;
	TextureManager healthTexture;
	TextureManager splashTexture;
	TextureManager missileTexture;
	TextureManager turretBaseTexture;
	TextureManager turretTextureOne;
	TextureManager coreTexture;
	TextureManager nebulaTexture2;
	TextureManager nebulaTexture3;
	TextureManager menuTexture;
	TextureManager turretSelectionMgr;
	TextureManager rulesMgr;
	TextureManager beginMgr;
	TextureManager info1mgr;
	TextureManager arrowMgr;
	TextureManager redMgr;
	TextureManager burstMgr;
	TextureManager sniperMgr;
	TextureManager triMgr;
	TextureManager pauseMgr;
	TriTurret triTurrets[5];
	SniperTurret sniperTurrets[5];
	Image red;
	Image pause;
	Image arrow;
	Image info1;
	Image rules;
	Image menu;
	Core core;
	Health begin;
    Ship    ship1;           // spaceships
	Missile missiles[50];
	BaseTurret baseTurrets[5];
	BurstTurret burstTurrets[5];
	Image spawners[4];
	int S1PerWaveMax;
	int S2PerWaveMax;
	int S3PerWaveMax;
	int S4PerWaveMax;
	int wavesLeft;
	int maxWaves;
	int enemyIndex;
	int roundsLeft;
	int maxRounds;
	bool pressed1;
	bool pressed2;
	bool pressed3;
	bool pressed4;
	bool pressed5;
	coreEnemy enemies[150];
	Missile turretMissiles1[50];
	Missile turretMissiles2[50];
	Missile turretMissiles3[50];
	Missile turretMissiles4[50];
	Missile turretMissiles5[50];
	Health health;
    Image   nebula;         // backdrop image
	Image turretBases[5];
	Image turret_selection;
	int colCounter;
	int missileIndex;
	int turretMissileIndex1;
	int turretMissileIndex2;
	int turretMissileIndex3;
	int turretMissileIndex4;
	int turretMissileIndex5;
	float turretTimer1;
	float turretTimer2;
	float turretTimer3;
	float turretTimer4;
	float turretTimer5;
	int spawnLoc;
	VECTOR2* fireVector;
	VECTOR2* forward;

	GAME_STATES gameState;
	bool flip;
	float tranTimer;
	float flipTimer;
	bool fired;
	bool turretFired1;
	bool turretFired2;
	bool turretFired3;
	bool turretFired4;
	bool turretFired5;
	int score;
	int turretPoints;
	bool level1;
	bool level2;
	bool level3;
	int turretAngle1;
	int turretAngle2;
	int turretAngle3;
	int turretAngle4;
	int turretAngle5;
	int EhealthMax;
	float turretMax;
	bool roundStart;
	float S1WaveMax;
	float S2WaveMax;
	float S3WaveMax;
	float S4WaveMax;
	float S1InWaveMax;
	float S2InWaveMax;
	float S3InWaveMax;
	float S4InWaveMax;
	float S1WaveTimer;
	float S2WaveTimer;
	float S3WaveTimer;
	float S4WaveTimer;
	float S1InWaveTimer;
	float S2InWaveTimer;
	float S3InWaveTimer;
	float S4InWaveTimer;
	float gameTimer;
	float increaseTime;
	int S1PerWave;
	int S2PerWave;
	int S3PerWave;
	int S4PerWave;
	int damageincrease;
	int healthincrease;
	int turretCost;
	int upgradeCost;
	bool gamePlaying;
	bool preGame;
	float tutTime;
	float realTime;
	float preGameTimer;
	TextDX *output;
	TextDX *outputHL;
	Image splash;
	std::string outString;
	std::string finalString;
	std::string swarmString;
	std::string introString1;
	std::string introString2;
	std::string introString3;
	std::string endString;
	std::string tutString;
	bool firstClick;
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

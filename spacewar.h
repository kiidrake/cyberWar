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
#include "kloss.h"
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
#include <fstream>
#include <sstream>
#include <string>
#include <istream>

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
	TextureManager bossMgr;
	TextureManager enemy2Mgr;
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
	int enemy2Index;
	int roundsLeft;
	int maxRounds;
	bool pressed1;
	bool pressed2;
	bool pressed3;
	bool pressed4;
	bool pressed5;
	coreEnemy enemies[150];
	coreEnemy enemies2[150];
	coreEnemy boss;
	Missile BaseTurretMissiles[400];
	Missile SniperTurretMissiles[200];
	Missile BurstTurretMissiles[200];
	
	Health health;
    Image   nebula;         // backdrop image
	Image turretBases[5];
	Image turret_selection;
	int colCounter;
	
	int BaseTurretMissileIndex;
	int SniperTurretMissileIndex;
	int BurstTurretMissileIndex;
	
	float BaseTurretTimer[5];
	float BurstTurretTimer[5];
	float SniperTurretTimer[5];
	float TriTurretTimer[5];
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
	int BaseTurretAngle[5];
	int TriTurretAngle[5];
	int BurstTurretAngle[5];
	int SniperTurretAngle[5];
	   std::ofstream saveGame_Score;
       std::ofstream saveGame_Level;
       std::ofstream highScore;
       std::ifstream in_saveGame_Score;
       std::ifstream in_saveGame_Level;
       std::ifstream in_highScore;

	int EhealthMax;
	int E2healthMax;
	float BaseTurretMax;
	float SniperTurretMax;
	float BurstTurretMax;
	float TriTurretMax;
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

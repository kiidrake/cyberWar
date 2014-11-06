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
    Ship    ship1;           // spaceships
	Missile missiles[50];
	Snake snakes[50];
	Armadillo armadillos[50];
	Spider spiders[50];
	Health health;
    Image   nebula;         // backdrop image
	int colCounter;
	int missileIndex;
	int spiderIndex;
	int armadilloIndex;
	int snakeIndex;
	int spawnLoc;
	bool fired;
	bool swarmFired;
	int score;
	bool swarmReady;
	float swarmTimer;
	float gameTimer;
	float increaseTime;
	float armadilloTimer;
	float spiderTimer;
	float snakeTimer;
	float maxArmadillo;
	float maxSnake;
	float maxSpider;
	bool spawnArmadillo;
	bool spawnSpider;
	bool spawnSnake;
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
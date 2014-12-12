// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and shield
// Chapter 6 spacewar.cpp v1.0
// This class is the core of the game

#include "spaceWar.h"
#include <cmath>
//=============================================================================
// Constructor
//=============================================================================
Spacewar::Spacewar()
{}

//=============================================================================
// Destructor
//=============================================================================
Spacewar::~Spacewar()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void Spacewar::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError
	audio->playCue(BACKGROUND);
    // nebula texture
	if(!pauseMgr.initialize(graphics,PAUSE_IMG))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash texture"));
	if(!splashTexture.initialize(graphics,SPLASH_SCREEN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash texture"));
	if(!triMgr.initialize(graphics,TRI_TURRET_IMG))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash texture"));
	if(!sniperMgr.initialize(graphics,SNIPER_TURRET_IMG))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash texture"));
	if(!burstMgr.initialize(graphics,BURST_TURRET_IMG))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash texture"));
	//if(!redMgr.initialize(graphics,RED))
		//throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash texture"));
	if(!arrowMgr.initialize(graphics,ARROW))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash texture"));
	if(!info1mgr.initialize(graphics,INFO1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash texture"));
	if(!beginMgr.initialize(graphics,BEGIN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash texture"));
	if(!menuTexture.initialize(graphics,MENU_IMG))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	if(!rulesMgr.initialize(graphics,RULES_PAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
    if (!nebulaTexture.initialize(graphics,NEBULA_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));
    if (!nebulaTexture2.initialize(graphics,NEBULA_IMAGE2))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture2"));
    if (!nebulaTexture3.initialize(graphics,NEBULA_IMAGE3))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture3"));
	if(!coreTexture.initialize(graphics,CORE_IMG))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing core texture"));
    // main game textures
	if(!turretBaseTexture.initialize(graphics,TURRET_BASE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret base texture"));
	if(!turretTextureOne.initialize(graphics,TURRET_IMAGE_ONE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret texture 1"));
    if (!gameTextures.initialize(graphics,SHIP_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));
	if (!snakeTexture.initialize(graphics,SNAKE_IMAGE))
		  throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing snake textures"));
	if(!spawnerTexture.initialize(graphics,ENEMY_SPAWNER_IMG))
		  throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spawner texture"));
	if(!enemyTexture.initialize(graphics,ENEMY_IMAGE))
		  throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy texture"));
	if(!splash.initialize(graphics,0,0,0,&splashTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash"));
	if(!turretSelectionMgr.initialize(graphics,TURRET_SELECTION))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret base texture"));

    // nebula image
	for(int i = 0; i < 5; i++){
		if(!turretBases[i].initialize(graphics,0,0,0,&turretBaseTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret base"));
	}
	for(int i = 0; i < 4; i++){
		if(!spawners[i].initialize(graphics,0,0,0,&spawnerTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spawners"));
	}
	if(!menu.initialize(graphics,0,0,0,&menuTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	if(!rules.initialize(graphics,0,0,0,&rulesMgr))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	if(!turret_selection.initialize(graphics,0,0,0,&turretSelectionMgr))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	if(!pause.initialize(graphics,0,0,0,&pauseMgr))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	if(!arrow.initialize(graphics,0,0,0,&arrowMgr))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	if(!info1.initialize(graphics,0,0,0,&info1mgr))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
	if(!red.initialize(graphics,0,0,0,&redMgr))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));
    if (!nebula.initialize(graphics,0,0,3,&nebulaTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

	nebula.setTextureManager(&nebulaTexture);


	if (!armadilloTexture.initialize(graphics,ARMADILLO_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing armadillo textures"));
	if (!spiderTexture.initialize(graphics,SPIDER_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spider textures"));
	if (!healthTexture.initialize(graphics,HEALTHBAR))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing healthbar"));
	if (!missileTexture.initialize(graphics,MISSILE_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing missile textures"));

	if (!health.initialize(this, healthNS::WIDTH, healthNS::HEIGHT, healthNS::TEXTURE_COLS, &healthTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
	if (!begin.initialize(this,800,600,2, &beginMgr))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
	begin.setFrames(0,1);
	begin.setFrameDelay(0.5f);
	begin.setCurrentFrame(healthNS::SHIP1_START_FRAME);
	begin.setX(0);
	begin.setY(0);
    health.setFrames(healthNS::SHIP1_START_FRAME, healthNS::SHIP1_START_FRAME);
	health.setCurrentFrame(ship1.getShipHealth());
    health.setX(375);
    health.setY(540);
	health.setVelocity(VECTOR2(healthNS::SPEED,-healthNS::SPEED)); // VECTOR2(X, Y)
	health.setScale(health.getScale() * 6);

    // ship
    if (!ship1.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, shipNS::TEXTURE_COLS, &gameTextures))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
    ship1.setFrames(shipNS::SHIP1_START_FRAME, shipNS::SHIP1_END_FRAME);
    ship1.setCurrentFrame(shipNS::SHIP1_START_FRAME);
    ship1.setX((GAME_WIDTH/2)-32);
	
    ship1.setY((GAME_HEIGHT/2)-32);
    ship1.setVelocity(VECTOR2(0,0)); // VECTOR2(X, Y)
	ship1.setScale(ship1.getScale() );
    // missile
	for( int i =0; i < 50; i++)
	{
		 if (!missiles[i].initialize(this, missileNS::WIDTH, missileNS::HEIGHT, missileNS::TEXTURE_COLS, &missileTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing missile1"));
		 missiles[i].setFrames(missileNS::SHIP1_START_FRAME, missileNS::SHIP1_END_FRAME);
		 missiles[i].setCurrentFrame(missileNS::SHIP1_START_FRAME);
		 missiles[i].setX(GAME_WIDTH/4);
		 missiles[i].setY(GAME_HEIGHT/4);
		 missiles[i].setVelocity(VECTOR2(missileNS::SPEED,-missileNS::SPEED)); // VECTOR2(X, Y)
		 missiles[i].setScale(missiles[i].getScale() * 2);
	}	
		for( int i =0; i < 50; i++)
	{
		if (!turretMissiles1[i].initialize(this, missileNS::WIDTH, missileNS::HEIGHT, missileNS::TEXTURE_COLS, &missileTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret missile1"));
		 turretMissiles1[i].setFrames(missileNS::SHIP1_START_FRAME, missileNS::SHIP1_END_FRAME);
		 turretMissiles1[i].setCurrentFrame(missileNS::SHIP1_START_FRAME);
		 turretMissiles1[i].setX(GAME_WIDTH/4);
		 turretMissiles1[i].setY(GAME_HEIGHT/4);
		 turretMissiles1[i].setVelocity(VECTOR2(missileNS::SPEED,-missileNS::SPEED)); // VECTOR2(X, Y)
		 turretMissiles1[i].setScale(turretMissiles1[i].getScale() * 2);
	}	
				for( int i =0; i < 50; i++)
	{
		if (!turretMissiles2[i].initialize(this, missileNS::WIDTH, missileNS::HEIGHT, missileNS::TEXTURE_COLS, &missileTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret missile1"));
		 turretMissiles2[i].setFrames(missileNS::SHIP1_START_FRAME, missileNS::SHIP1_END_FRAME);
		 turretMissiles2[i].setCurrentFrame(missileNS::SHIP1_START_FRAME);
		 turretMissiles2[i].setX(GAME_WIDTH/4);
		 turretMissiles2[i].setY(GAME_HEIGHT/4);
		 turretMissiles2[i].setVelocity(VECTOR2(missileNS::SPEED,-missileNS::SPEED)); // VECTOR2(X, Y)
		 turretMissiles2[i].setScale(turretMissiles2[i].getScale() * 2);
	}	
						for( int i =0; i < 50; i++)
	{
		if (!turretMissiles3[i].initialize(this, missileNS::WIDTH, missileNS::HEIGHT, missileNS::TEXTURE_COLS, &missileTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret missile1"));
		 turretMissiles3[i].setFrames(missileNS::SHIP1_START_FRAME, missileNS::SHIP1_END_FRAME);
		 turretMissiles3[i].setCurrentFrame(missileNS::SHIP1_START_FRAME);
		 turretMissiles3[i].setX(GAME_WIDTH/4);
		 turretMissiles3[i].setY(GAME_HEIGHT/4);
		 turretMissiles3[i].setVelocity(VECTOR2(missileNS::SPEED,-missileNS::SPEED)); // VECTOR2(X, Y)
		 turretMissiles3[i].setScale(turretMissiles3[i].getScale() * 2);
	}	
								for( int i =0; i < 50; i++)
	{
		if (!turretMissiles4[i].initialize(this, missileNS::WIDTH, missileNS::HEIGHT, missileNS::TEXTURE_COLS, &missileTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret missile1"));
		 turretMissiles4[i].setFrames(missileNS::SHIP1_START_FRAME, missileNS::SHIP1_END_FRAME);
		 turretMissiles4[i].setCurrentFrame(missileNS::SHIP1_START_FRAME);
		 turretMissiles4[i].setX(GAME_WIDTH/4);
		 turretMissiles4[i].setY(GAME_HEIGHT/4);
		 turretMissiles4[i].setVelocity(VECTOR2(missileNS::SPEED,-missileNS::SPEED)); // VECTOR2(X, Y)
		 turretMissiles4[i].setScale(turretMissiles4[i].getScale() * 2);
	}	
										for( int i =0; i < 50; i++)
	{
		if (!turretMissiles1[i].initialize(this, missileNS::WIDTH, missileNS::HEIGHT, missileNS::TEXTURE_COLS, &missileTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing turret missile1"));
		 turretMissiles5[i].setFrames(missileNS::SHIP1_START_FRAME, missileNS::SHIP1_END_FRAME);
		 turretMissiles5[i].setCurrentFrame(missileNS::SHIP1_START_FRAME);
		 turretMissiles5[i].setX(GAME_WIDTH/4);
		 turretMissiles5[i].setY(GAME_HEIGHT/4);
		 turretMissiles5[i].setVelocity(VECTOR2(missileNS::SPEED,-missileNS::SPEED)); // VECTOR2(X, Y)
		 turretMissiles5[i].setScale(turretMissiles5[i].getScale() * 2);
	}	
	for(int i = 0;i < 5; i++){
		if (!baseTurrets[i].initialize(this, BaseTurretNS::WIDTH, BaseTurretNS::HEIGHT, BaseTurretNS::TEXTURE_COLS, &turretTextureOne))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing base turrets"));	
		baseTurrets[i].setFrames(BaseTurretNS::SHIP1_START_FRAME,BaseTurretNS::SHIP1_END_FRAME);
		baseTurrets[i].setCurrentFrame(BaseTurretNS::SHIP1_START_FRAME);
		baseTurrets[i].setActive(false);
		baseTurrets[i].setDone(true);
	}
	for(int i = 0;i < 5; i++){
		if (!burstTurrets[i].initialize(this, BurstTurretNS::WIDTH, BurstTurretNS::HEIGHT, BurstTurretNS::TEXTURE_COLS, &burstMgr))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing base turrets"));	
		burstTurrets[i].setFrames(BurstTurretNS::SHIP1_START_FRAME,BurstTurretNS::SHIP1_END_FRAME);
		burstTurrets[i].setCurrentFrame(BaseTurretNS::SHIP1_START_FRAME);
		burstTurrets[i].setActive(false);
		burstTurrets[i].setDone(true);
	}
	for(int i = 0;i < 5; i++){
		if (!sniperTurrets[i].initialize(this, SniperTurretNS::WIDTH, SniperTurretNS::HEIGHT, SniperTurretNS::TEXTURE_COLS, &sniperMgr))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing base turrets"));	
		sniperTurrets[i].setFrames(SniperTurretNS::SHIP1_START_FRAME,SniperTurretNS::SHIP1_END_FRAME);
		sniperTurrets[i].setCurrentFrame(SniperTurretNS::SHIP1_START_FRAME);
		sniperTurrets[i].setActive(false);
		sniperTurrets[i].setDone(true);
	}
	for(int i = 0;i < 5; i++){
		if (!triTurrets[i].initialize(this, TriTurretNS::WIDTH, TriTurretNS::HEIGHT, TriTurretNS::TEXTURE_COLS, &triMgr))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing base turrets"));	
		triTurrets[i].setFrames(TriTurretNS::SHIP1_START_FRAME,TriTurretNS::SHIP1_END_FRAME);
		triTurrets[i].setCurrentFrame(TriTurretNS::SHIP1_START_FRAME);
		triTurrets[i].setActive(false);
		triTurrets[i].setDone(true);
	}
	for( int i =0; i < 50; i++)
	{
		if (!enemies[i].initialize(this, coreEnemyNS::WIDTH, coreEnemyNS::HEIGHT, coreEnemyNS::TEXTURE_COLS, &enemyTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing missile1"));
		 enemies[i].setFrames(coreEnemyNS::SHIP1_START_FRAME, coreEnemyNS::SHIP1_END_FRAME);
		 enemies[i].setCurrentFrame(coreEnemyNS::SHIP1_START_FRAME);
		 enemies[i].setX(GAME_WIDTH/4);
		 enemies[i].setY(GAME_HEIGHT/4);
		 enemies[i].setVelocity(VECTOR2(coreEnemyNS::SPEED,-coreEnemyNS::SPEED)); // VECTOR2(X, Y)
	}
	if(!core.initialize(this,CoreNS::WIDTH,CoreNS::HEIGHT,0,&coreTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing core"));
	core.setFrames(0,0);
    core.setCurrentFrame(0);
    core.setX(1500);
    core.setY(1100);                        
	core.setActive(true);
	core.setScale(core.getScale() *2);

	outString = "Score: ";
	finalString = "Game Over \nFinalScore: ";
	swarmString = "Swarm Ready, Press Shift to Fire";
	introString1 = "A strange force has caused the creatures in the forest outside your town to attack.\nDefend your town, but do not allow the creaturs to destroy your hovercraft";
	introString2 = "You are the last hope";
	introString3 = "Arrow keys to move, space to fire, shift for special attack";
	output = new TextDX();
	outputHL = new TextDX();
	if(output->initialize(graphics, 20, true, false, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing output font"));

	if(outputHL->initialize(graphics, 20, true, true, "Arial") == false)
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing output font"));

	turretBases[0].setX(500);
	turretBases[0].setY(1000);
	turretBases[1].setX(700);
	turretBases[1].setY(700);
	turretBases[2].setX(900);
	turretBases[2].setY(500);
	turretBases[3].setX(1100);
	turretBases[3].setY(300);
	turretBases[4].setX(1300);
	turretBases[4].setY(100);

	spawners[0].setX(100);
	spawners[0].setY(200);
	spawners[1].setX(100);
	spawners[1].setY(700);
	spawners[2].setX(600);
	spawners[2].setY(100);
	spawners[3].setX(1000);
	spawners[3].setY(100);
		turret_selection.setX(140);
	turret_selection.setY(500);
	core.setX(1300);
	core.setY(900);

	outputHL->setFontColor(graphicsNS::RED);
	gameState = TITLESCREEN;
	level1 = false;
	level2 = false;
	level3 = false;
	preGame = true;
    gamePlaying = true;
	score = 0;
	colCounter = 0;
	missileIndex= 0;
	turretMissileIndex1 = 0;
	turretMissileIndex2 = 0;
	turretMissileIndex3 = 0;
	turretMissileIndex4 = 0;
	turretMissileIndex5 = 0;
	turretTimer1 = 0.5;
	turretTimer2 = 0.5;
	turretTimer3 = 0.5;
	turretTimer4 = 0.5;
	turretTimer5 = 0.5;
	fired = false;
	enemyIndex = 0;
	S1PerWaveMax = 5;
	S2PerWaveMax = 5;
	S3PerWaveMax = 5;
	S4PerWaveMax = 5;
	firstClick = false;
	wavesLeft = 12;
	maxWaves = 12;
	gameTimer = 0;
	increaseTime = 2.0;
	EhealthMax = 111;
	turretMax= 0.5;
	roundStart = false;
    S1WaveMax =  20;
    S2WaveMax = 20;
    S3WaveMax = 20;
	S4WaveMax = 20;
	S1InWaveMax = 0.5;
	S2InWaveMax = 0.5;
	S3InWaveMax = 0.5;
	S4InWaveMax = 0.5;
	S1WaveTimer = 5;
	S2WaveTimer = 15;
	S3WaveTimer = 25;
	S4WaveTimer = 35;
	S1InWaveTimer = 0.5;
	S2InWaveTimer = 0.5;
	S3InWaveTimer = 0.5;
	S4InWaveTimer = 0.5;
	turretPoints = 10;
    S1PerWave = 5;
	S2PerWave = 5;
	S3PerWave = 5;
	S4PerWave = 5;
	damageincrease = 1;
	healthincrease = 1;
	roundsLeft = 3;
	maxRounds = 3;
	turretCost = 10;
	upgradeCost = 5;
	preGameTimer = 8.0;
	pressed1 = false;
	pressed2 = false;
	pressed3 = false;
	pressed4 = false;
	pressed5 = false;
	srand (time(NULL));
	info1.setX(285);
	info1.setY(440);
	arrow.setX(385);
	arrow.setY(440);
    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	switch(gameState){
	case(TITLESCREEN):
		if(input->isKeyDown(VK_RETURN)){
			gameState = MENU;
		}
		break;

	case(GAMEPLAY):
	if(roundStart == false)	begin.update(frameTime);
	if(roundStart == false && input->isKeyDown(VK_ESCAPE)) gameState = PAUSE;
	if (input->isKeyDown(VK_RETURN))
	{
		roundStart = true;
	}
	tutTime = gameTimer;
	//TURRET 1 CLICK & DRAG
	if(input->getMouseX() > 282 && input->getMouseX() < 282+64 && input->getMouseY() < 520 && input->getMouseY() > 460 && input->getMouseLButton())
	{
		 firstClick = true; 
		for(int i = 0; i < 5; i++)
		{
			if(!(baseTurrets[i].getActive()) && turretPoints >= 10)
			{
				baseTurrets[i].setActive(true);
				baseTurrets[i].setDone(false);
				baseTurrets[i].setX(input->getMouseX());
				baseTurrets[i].setY(input->getMouseY());
				turretPoints -= 10;
			}
	}
	}
	if(firstClick == true)
	{
		for(int i = 0; i < 5; i++)
		{
			if(!baseTurrets[i].getDone())
			{
				baseTurrets[i].setX(input->getMouseX());
				baseTurrets[i].setY(input->getMouseY());
			}
		}
		if(input->getMouseRButton())
		{
			for(int i = 0; i < 5; i++)
			{
				if(!baseTurrets[i].getDone())
				{
					baseTurrets[i].setX(input->getMouseX());
					baseTurrets[i].setY(input->getMouseY());
					baseTurrets[i].setDone(true);
					firstClick = false;
				}
			}
		}
	}

	//TURRET 2 CLICK & DRAG
	if(input->getMouseX() > 282+64 && input->getMouseX() < 282+128 && input->getMouseY() < 520 && input->getMouseY() > 460 && input->getMouseLButton())
	{
		firstClick = true; 
		for(int i = 0; i < 5; i++)
		{
			if(!(burstTurrets[i].getActive()) && turretPoints >= 15)
			{
				burstTurrets[i].setActive(true);
				burstTurrets[i].setDone(false);
				burstTurrets[i].setX(input->getMouseX());
				burstTurrets[i].setY(input->getMouseY());
				turretPoints -= 15;
			}
		}
	}
	if(firstClick == true)
	{
		for(int i = 0; i < 5; i++)
		{
			if(!burstTurrets[i].getDone())
			{
				burstTurrets[i].setX(input->getMouseX());
				burstTurrets[i].setY(input->getMouseY());
			}
		}
		if(input->getMouseRButton())
		{
			for(int i = 0; i < 5; i++)
			{
				if(!burstTurrets[i].getDone())
				{
					burstTurrets[i].setX(input->getMouseX());
					burstTurrets[i].setY(input->getMouseY());
					burstTurrets[i].setDone(true);
					firstClick = false;
				}
			}
		}
	}
	//TURRET 3 CLICK & DRAG
	if(input->getMouseX() > 282+128 && input->getMouseX() < 282+256 && input->getMouseY() < 520 && input->getMouseY() > 460 && input->getMouseLButton()) 
	{
		firstClick = true; 
		for(int i = 0; i < 5; i++)
		{
			if(!(sniperTurrets[i].getActive()) && turretPoints >= 20)
			{
				sniperTurrets[i].setActive(true);
				sniperTurrets[i].setDone(false);
				sniperTurrets[i].setX(input->getMouseX());
				sniperTurrets[i].setY(input->getMouseY());
				turretPoints -= 20;
			}
		}
	}
	if(firstClick == true)
	{
		for(int i = 0; i < 5; i++)
		{
			if(!sniperTurrets[i].getDone())
			{
				sniperTurrets[i].setX(input->getMouseX());
				sniperTurrets[i].setY(input->getMouseY());
			}
		}
		if(input->getMouseRButton())
		{
			for(int i = 0; i < 5; i++)
			{
				if(!sniperTurrets[i].getDone())
				{
					sniperTurrets[i].setX(input->getMouseX());
					sniperTurrets[i].setY(input->getMouseY());
					sniperTurrets[i].setDone(true);
					firstClick = false;
				}
			}
		}
	}
	//TURRET 4 CLICK & DRAG
	if(input->getMouseX() > 282+256 && input->getMouseX() < (282+64+256) && input->getMouseY() < 520 && input->getMouseY() > 460 && input->getMouseLButton()) 
	{
		firstClick = true; 
		for(int i = 0; i < 5; i++)
		{
			if(!(triTurrets[i].getActive()) && turretPoints >= 25)
			{
				triTurrets[i].setActive(true);
				triTurrets[i].setDone(false);
				triTurrets[i].setX(input->getMouseX());
				triTurrets[i].setY(input->getMouseY());
				turretPoints -= 25;
			}
		}
	}
	if(firstClick == true)
	{
		for(int i = 0; i < 5; i++)
		{
			if(!triTurrets[i].getDone())
			{
				triTurrets[i].setX(input->getMouseX());
				triTurrets[i].setY(input->getMouseY());
			}
		}
		if(input->getMouseRButton())
		{
			for(int i = 0; i < 5; i++)
			{
				if(!triTurrets[i].getDone())
				{
					triTurrets[i].setX(input->getMouseX());
					triTurrets[i].setY(input->getMouseY());
					triTurrets[i].setDone(true);
					firstClick = false;
				}
			}
		}
	}

	if (input-> isKeyDown(0x39))
	{
		core.setCoreHealthe(100);
	}
	if (input-> isKeyDown(0x30))
	{
		turretPoints = 1000;
	}
	
	angle = atan2(core.getY() - arrow.getY(), core.getX() - arrow.getX());
	angle *= (180/PI);
	arrow.setDegrees(90 + angle);
	arrow.update(frameTime);
	ship1.setX(input->getMouseX());
	ship1.setY(input->getMouseY());

	if (ship1.getShipHealth() <= 0)
	{
		gamePlaying = false;																								
		audio->stopCue(BACKGROUND);
	}
    
	gameTimer += frameTime;
	
	turretTimer1 -= frameTime;
	turretTimer2 -= frameTime;
	turretTimer3 -= frameTime;
	turretTimer4 -= frameTime;
	turretTimer5 -= frameTime;


	//	for(int i = 0; i < 5; i++){
	//		if(baseTurrets[i].getActive()){
	//			baseTurrets[i].setDegrees(angle);
	//		}
	//}
	

	if (nebula.getX() <= 0 && ((ship1.getX())*ship1.getScale()) >= (GAME_WIDTH) - 10 && ((ship1.getX())*ship1.getScale()) <= (GAME_WIDTH) + 10  && nebula.getX()  >= (int)GAME_WIDTH - (int)BACK_WIDTH && ship1.getX() < BACK_WIDTH)
	{
		if(ship1.getVelocity() < 0) ship1.setVelocity(VECTOR2(ship1.getVelocity().x*-1,ship1.getVelocity().y*-1));
		if(ship1.getX() >=0){
		for(int i = 0; i < 5; i++)
		{
			turretBases[i].setX(turretBases[i].getX() - frameTime * ship1.getVelocity().x);
			
			baseTurrets[i].setX(baseTurrets[i].getX() - frameTime * ship1.getVelocity().x);
		
		}
				for(int i = 0; i < 50; i++){
			missiles[i].setX(missiles[i].getX() - frameTime * ship1.getVelocity().x);
			turretMissiles1[i].setX(turretMissiles1[i].getX() - frameTime * ship1.getVelocity().x);
			turretMissiles2[i].setX(turretMissiles2[i].getX() - frameTime * ship1.getVelocity().x);
			turretMissiles3[i].setX(turretMissiles3[i].getX() - frameTime * ship1.getVelocity().x);
			turretMissiles4[i].setX(turretMissiles4[i].getX() - frameTime * ship1.getVelocity().x);
			turretMissiles5[i].setX(turretMissiles5[i].getX() - frameTime * ship1.getVelocity().x);
			enemies[i].setX(enemies[i].getX() - frameTime * ship1.getVelocity().x);
		}
				for(int i = 0; i < 4; i++){
					spawners[i].setX(spawners[i].getX() - frameTime * ship1.getVelocity().x);
				}
				core.setX(core.getX() - frameTime * ship1.getVelocity().x);
		nebula.setX(nebula.getX() - frameTime * ship1.getVelocity().x);
		}
		
	}	
	
	else 
	{
		if (nebula.getX() > 0 )
		{
			nebula.setX(0);
		}
		if (nebula.getX() < ((int)GAME_WIDTH - (int)BACK_WIDTH))
		{
			nebula.setX(((int)GAME_WIDTH - (int)BACK_WIDTH));
		}
		ship1.setX(ship1.getX() + frameTime * ship1.getVelocity().x);
	}
	
	if (nebula.getY() <= 0 && (ship1.getY())*ship1.getScale() >= (GAME_HEIGHT) - 10 && (ship1.getY())*ship1.getScale() <= (GAME_HEIGHT) + 10  && nebula.getY()  >= (int)GAME_HEIGHT - (int)BACK_HEIGHT && ship1.getY() < BACK_HEIGHT)
	{
		for(int i = 0; i < 5; i++)
		{
			
			turretBases[i].setY(turretBases[i].getY() - frameTime * ship1.getVelocity().y);
			
			baseTurrets[i].setY(baseTurrets[i].getY() - frameTime * ship1.getVelocity().y);
		}
		for(int i = 0; i < 50; i++){
			missiles[i].setY(missiles[i].getY() - frameTime * ship1.getVelocity().y);
			turretMissiles1[i].setY(turretMissiles1[i].getY() - frameTime * ship1.getVelocity().y);
			turretMissiles2[i].setY(turretMissiles2[i].getY() - frameTime * ship1.getVelocity().y);
			turretMissiles3[i].setY(turretMissiles3[i].getY() - frameTime * ship1.getVelocity().y);
			turretMissiles4[i].setY(turretMissiles4[i].getY() - frameTime * ship1.getVelocity().y);
			turretMissiles5[i].setY(turretMissiles5[i].getY() - frameTime * ship1.getVelocity().y);
			enemies[i].setY(enemies[i].getY() - frameTime * ship1.getVelocity().y);
		}
		for(int i = 0; i < 4; i++){
			spawners[i].setY(spawners[i].getY() - frameTime * ship1.getVelocity().y);
		}
		core.setY(core.getY() - frameTime * ship1.getVelocity().y);
		nebula.setY(nebula.getY() - frameTime * ship1.getVelocity().y);
		
	}
	
	else 
	{
		if (nebula.getY() > 0 )
		{
			nebula.setY(0);
		}
		if (nebula.getY() < ((int)GAME_HEIGHT - (int)BACK_HEIGHT) )
		{
			nebula.setY(((int)GAME_HEIGHT - (int)BACK_HEIGHT));
		}
		ship1.setY(ship1.getY() + frameTime * ship1.getVelocity().y);
	}
	////////////////////////////////////////////////
if (nebula.getX() <= 0 && ((ship1.getX()*ship1.getScale())) <= 10 && ((ship1.getX())*ship1.getScale()) <= 10  && nebula.getX()  >= (int)GAME_WIDTH - (int)BACK_WIDTH && ship1.getX() < BACK_WIDTH)
	{
		ship1.setVelocity(VECTOR2(ship1.getVelocity().x*-1,ship1.getVelocity().y*-1));
	
		for(int i = 0; i < 5; i++)
		{
			turretBases[i].setX(turretBases[i].getX() - frameTime * ship1.getVelocity().x);
			
			baseTurrets[i].setX(baseTurrets[i].getX() - frameTime * ship1.getVelocity().x);
		
		}
				for(int i = 0; i < 50; i++){
			missiles[i].setX(missiles[i].getX() - frameTime * ship1.getVelocity().x);
			turretMissiles1[i].setX(turretMissiles1[i].getX() - frameTime * ship1.getVelocity().x);
			turretMissiles2[i].setX(turretMissiles2[i].getX() - frameTime * ship1.getVelocity().x);
			turretMissiles3[i].setX(turretMissiles3[i].getX() - frameTime * ship1.getVelocity().x);
			turretMissiles4[i].setX(turretMissiles4[i].getX() - frameTime * ship1.getVelocity().x);
			turretMissiles5[i].setX(turretMissiles5[i].getX() - frameTime * ship1.getVelocity().x);
			enemies[i].setX(enemies[i].getX() - frameTime * ship1.getVelocity().x);
		}
				for(int i = 0; i < 4; i++){
					spawners[i].setX(spawners[i].getX() - frameTime * ship1.getVelocity().x);
				}
				core.setX(core.getX() - frameTime * ship1.getVelocity().x);
		nebula.setX(nebula.getX() - frameTime * ship1.getVelocity().x);
		
	}	
	
	else 
	{
		if (nebula.getX() > 0 )
		{
			nebula.setX(0);
		}
		if (nebula.getX() < ((int)GAME_WIDTH - (int)BACK_WIDTH))
		{
			nebula.setX(((int)GAME_WIDTH - (int)BACK_WIDTH));
		}
		ship1.setX(ship1.getX() + frameTime * ship1.getVelocity().x);
	}
	if (nebula.getY() <= 0 && (ship1.getY() *ship1.getScale()) <= 10 && (ship1.getY())*ship1.getScale() <= 10  && nebula.getY()  >= (int)GAME_HEIGHT - (int)BACK_HEIGHT && ship1.getY() < BACK_HEIGHT)
	{
		ship1.setVelocity(VECTOR2(ship1.getVelocity().x*-1,ship1.getVelocity().y*-1));
		for(int i = 0; i < 5; i++)
		{
			
			turretBases[i].setY(turretBases[i].getY() - frameTime * ship1.getVelocity().y);
			
			baseTurrets[i].setY(baseTurrets[i].getY() - frameTime * ship1.getVelocity().y);
		}
		for(int i = 0; i < 50; i++){
			missiles[i].setY(missiles[i].getY() - frameTime * ship1.getVelocity().y);
			turretMissiles1[i].setY(turretMissiles1[i].getY() - frameTime * ship1.getVelocity().y);
			turretMissiles2[i].setY(turretMissiles2[i].getY() - frameTime * ship1.getVelocity().y);
			turretMissiles3[i].setY(turretMissiles3[i].getY() - frameTime * ship1.getVelocity().y);
			turretMissiles4[i].setY(turretMissiles4[i].getY() - frameTime * ship1.getVelocity().y);
			turretMissiles5[i].setY(turretMissiles5[i].getY() - frameTime * ship1.getVelocity().y);
			enemies[i].setY(enemies[i].getY() - frameTime * ship1.getVelocity().y);
		}
		for(int i = 0; i < 4; i++){
			spawners[i].setY(spawners[i].getY() - frameTime * ship1.getVelocity().y);
		}
		core.setY(core.getY() - frameTime * ship1.getVelocity().y);
		nebula.setY(nebula.getY() - frameTime * ship1.getVelocity().y);
		
	}
	
	else 
	{
		if (nebula.getY() > 0 )
		{
			nebula.setY(0);
		}
		if (nebula.getY() < ((int)GAME_HEIGHT - (int)BACK_HEIGHT) )
		{
			nebula.setY(((int)GAME_HEIGHT - (int)BACK_HEIGHT));
		}
		ship1.setY(ship1.getY() + frameTime * ship1.getVelocity().y);
	}
	///////////////////////////////////////////////////


	if ((input->isKeyDown(VK_SPACE)) && !fired )
	{
		audio->playCue(FIRE);
		//missiles[missileIndex].setDegrees(angle);
	 missiles[missileIndex].setX(ship1.getX());
	 missiles[missileIndex].setY(ship1.getY());
	 VECTOR2 fVec(input->getMouseX() - ship1.getX(), input->getMouseY() - ship1.getY());
	 D3DXVec2Normalize(&fVec, &fVec); 
	 missiles[missileIndex].setVelocity(fVec);
	
	 missiles[missileIndex].activate();
	 missileIndex++;
	 
	 fired = true;
	} 
	else if ((input->isKeyDown(VK_SPACE)) && fired )
	{
    
	} 
	else
	{
		fired = false;
	}

	for( int i =0; i < 50; i++)
	{
	
	  
	  missiles[i].update(frameTime);
	}

	if (missileIndex >=50)
	{
		missileIndex = 0;
	}
		for( int i =0; i < 50; i++) 
	{
	
	  
		turretMissiles1[i].update(frameTime);
	}
	
	if (turretMissileIndex1 >=50)
	{
		turretMissileIndex1 = 0;
	}
	for( int i =0; i < 50; i++)
	{
				
		
		turretMissiles2[i].update(frameTime); 
	}
	
	if (turretMissileIndex2 >=50)
	{
		turretMissileIndex2 = 0;
	}
	for( int i =0; i < 50; i++)
	{
	
	  
		turretMissiles3[i].update(frameTime);
	}
	
	if (turretMissileIndex3 >=50)
	{
		turretMissileIndex3 = 0;
	}
	for( int i =0; i < 50; i++)
	{
	
	  
		turretMissiles4[i].update(frameTime);
	}
	
	if (turretMissileIndex4 >=50)
	{
		turretMissileIndex4 = 0;
	}
	for( int i =0; i < 50; i++)
	{
	
	  
		turretMissiles5[i].update(frameTime);
	}
	
	if (turretMissileIndex5 >=50)
	{
		turretMissileIndex5 = 0;
	}
			if(input->isKeyDown(VK_LSHIFT)){
		core.setCoreHealthe(10000);
	}
	if(input->isKeyDown(VK_RSHIFT)){
		turretPoints = 10000;
	}
	if(core.getCoreHealth() == 10 || core.getCoreHealth() == 9){
		health.setCurrentFrame(5);
	}
	if(core.getCoreHealth() == 8 || core.getCoreHealth() == 7){
		health.setCurrentFrame(4);
	}
	if(core.getCoreHealth() == 6 || core.getCoreHealth() == 5) health.setCurrentFrame(3);
	if(core.getCoreHealth() == 4 || core.getCoreHealth() == 3) health.setCurrentFrame(2);
	if(core.getCoreHealth() == 2 || core.getCoreHealth() == 1) health.setCurrentFrame(1);
	if(core.getCoreHealth() == 0) health.setCurrentFrame(0);
	
	core.update(frameTime);

	for(int i = 0; i < 150; i++){
		for(int j = 0; i < 5; i++){
			if(enemies[i].getCenterX() > baseTurrets[j].getX() && enemies[i].getCenterX() < (baseTurrets[j].getX() + baseTurrets[j].getWidth())
				&& enemies[i].getCenterY() > baseTurrets[j].getY() && enemies[i].getCenterY() < (baseTurrets[j].getY() + baseTurrets[j].getHeight())){
					enemies[i].setActive(false);
					baseTurrets[j].setActive(false);
			}
			if(enemies[i].getCenterX() > burstTurrets[j].getX() && enemies[i].getCenterX() < (burstTurrets[j].getX() + burstTurrets[j].getWidth())
				&& enemies[i].getCenterY() > burstTurrets[j].getY() && enemies[i].getCenterY() < (burstTurrets[j].getY() + burstTurrets[j].getHeight())){
					enemies[i].setActive(false);
					burstTurrets[j].setActive(false);
			}
			if(enemies[i].getCenterX() > sniperTurrets[j].getX() && enemies[i].getCenterX() < (sniperTurrets[j].getX() + sniperTurrets[j].getWidth())
				&& enemies[i].getCenterY() > sniperTurrets[j].getY() && enemies[i].getCenterY() < (sniperTurrets[j].getY() + sniperTurrets[j].getHeight())){
					enemies[i].setActive(false);
					sniperTurrets[j].setActive(false);
			}
			if(enemies[i].getCenterX() > triTurrets[j].getX() && enemies[i].getCenterX() < (triTurrets[j].getX() + triTurrets[j].getWidth())
				&& enemies[i].getCenterY() > triTurrets[j].getY() && enemies[i].getCenterY() < (triTurrets[j].getY() + triTurrets[j].getHeight())){
					enemies[i].setActive(false);
					triTurrets[j].setActive(false);
			}
		}
	}
	//TURRET MISSILES
	
	//TURRET MISSILES

	//TURRET MISSILES

	//TURRET MISSILES
	
	//TURRET MISSILES
	for(int i = 0; i < 50; i++){
		if (enemies[i].getEnemyHealth() <= 0)
		{
			enemies[i].setActive(false);
			enemies[i].setEnemyHealth(EhealthMax);
			score += 100;
			turretPoints+= 1;

		}
	}
	if (core.getCoreHealth() <= 0)
	{
		core.setActive(false);
		gameState = GAMEOVER;
		endString = "YOU LOSE";
	}
	ship1.update(frameTime);
	if (roundStart)
	{
		S1WaveTimer -= frameTime;
		S2WaveTimer -= frameTime;
		S3WaveTimer -= frameTime;
		S4WaveTimer -= frameTime;
		if (S1WaveTimer <= 0)
		{
			S1InWaveTimer -= frameTime;
			if (S1InWaveTimer <= 0)
			{
				enemies[enemyIndex].setX(spawners[0].getCenterX());
				enemies[enemyIndex].setY(spawners[0].getCenterY());
				if (!level2)
				{
					enemies[enemyIndex].setPattern(RIGHT,DOWN,DOWNRIGHT,TRACK);
				}
				else if (level2)
				{
					enemies[enemyIndex].setPattern(RIGHT,DOWN,LEFT,TRACK);
				}
				enemies[enemyIndex].setPatternTime(3,2,2.5,30);
			    enemies[enemyIndex].activate();
				enemyIndex++;
				if (enemyIndex >=50)
				{
					enemyIndex = 0;
				}
				
				S1InWaveTimer = S1InWaveMax;
				S1PerWave -= 1;
				if (S1PerWave == 0)
				{
					S1PerWave = S1PerWaveMax;
					S1WaveTimer = S1WaveMax;
					wavesLeft -= 1;
				}


			}
		}
			if (S2WaveTimer <= 0)
		{
			S2InWaveTimer -= frameTime;
			if (S2InWaveTimer <= 0)
			{
				enemies[enemyIndex].setX(spawners[1].getCenterX());
				enemies[enemyIndex].setY(spawners[1].getCenterY());
				if (!level2)
				{
					enemies[enemyIndex].setPattern(RIGHT,UP,DOWNRIGHT,TRACK);
				}
				else if (level2)
				{
					enemies[enemyIndex].setPattern(UPRIGHT,DOWN,DOWNRIGHT,TRACK);
				}
				enemies[enemyIndex].setPatternTime(2,3,2.5,30);
			    enemies[enemyIndex].activate();
				enemyIndex++;
				if (enemyIndex >=50)
				{
					enemyIndex = 0;
				}
				S2InWaveTimer = S2InWaveMax;
				S2PerWave -= 1;
				if (S2PerWave == 0)
				{
					S2PerWave = S2PerWaveMax;
					S2WaveTimer = S2WaveMax;
					wavesLeft -= 1;

				}


			}
		  }
			if (S3WaveTimer <= 0)
		{
			S3InWaveTimer -= frameTime;
			if (S3InWaveTimer <= 0)
			{
				enemies[enemyIndex].setX(spawners[2].getCenterX());
				enemies[enemyIndex].setY(spawners[2].getCenterY());
				if (!level2)
				{
					enemies[enemyIndex].setPattern(RIGHT,DOWN,DOWNRIGHT,TRACK);
				}
				else if (level2)
				{
					enemies[enemyIndex].setPattern(UP,LEFT,RIGHT,TRACK);
				}
				enemies[enemyIndex].setPatternTime(2,3,2.5,30);
			    enemies[enemyIndex].activate();
				enemyIndex++;
				if (enemyIndex >=50)
				{
					enemyIndex = 0;
				}
				S3InWaveTimer = S3InWaveMax;
				S3PerWave -= 1;
				if (S3PerWave == 0)
				{
					S3PerWave = S3PerWaveMax;
					S3WaveTimer = S3WaveMax;
					wavesLeft -= 1;

				}
			}
		}
		if (S4WaveTimer <= 0)
		{
			S4InWaveTimer -= frameTime;
			if (S4InWaveTimer <= 0)
			{
				enemies[enemyIndex].setX(spawners[3].getCenterX());
				enemies[enemyIndex].setY(spawners[3].getCenterY());
				
				if (!level2)
				{
					enemies[enemyIndex].setPattern(DOWN,LEFT,DOWNRIGHT,TRACK);
				}
				else if (level2)
				{
					enemies[enemyIndex].setPattern(UPLEFT,DOWN,DOWNLEFT,TRACK);
				}
				enemies[enemyIndex].setPatternTime(2,3,2.5,30);
			    enemies[enemyIndex].activate();
				enemyIndex++;
				if (enemyIndex >=50)
				{
					enemyIndex = 0;
				}
				S4InWaveTimer = S4InWaveMax;
				S4PerWave -= 1;
				if (S4PerWave == 0)
				{
					S4PerWave = S4PerWaveMax;
					S4WaveTimer = S4WaveMax;
					wavesLeft -= 1;

				}


			}
		}
		if (wavesLeft <= 0)
		{
			wavesLeft = maxWaves;
			roundStart = false;
			roundsLeft -= 1;
			EhealthMax += 1;
			for(int i = 0; i < 50; i++){
			enemies[i].setActive(false);
			enemies[i].setEnemyHealth(EhealthMax);
			}
			S1PerWaveMax += 1;
			S2PerWaveMax += 1;
			S3PerWaveMax += 1;
			S4PerWaveMax += 1;
			S1PerWave = S1PerWaveMax;
			S2PerWave = S2PerWaveMax;
			S3PerWave = S3PerWaveMax;
			S4PerWave = S4PerWaveMax;
			

			
			
			S1WaveTimer = 5;
			S2WaveTimer = 15;
			S3WaveTimer = 25;
			S4WaveTimer = 35;
		}
	
		if (roundsLeft <= 0)
		{
			roundsLeft = maxRounds;
			if (level1 == true)
			{
				gameState = TRAN1;
			}
			if (level2 == true)
			{
				gameState = TRAN2;
			}
			if (level3 == true)
			{
				gameState = GAMEOVER;
				endString = "YOU WIN";
			}
			
		}
			for(int i = 0; i < 50; i++){
		enemies[i].update(frameTime);
	}
				if(input->isKeyDown(ESC_KEY)){
					gameState = PAUSE;
	}
	
	}
	
	break;
	case(MENU):

		core.setCoreHealthe(10);
		core.setActive(true);
		for (int i = 0; i < 50; i++)
		{
			enemies[i].setActive(false);
			enemies[i].setEnemyHealth(1);
		}
		for (int i = 0; i < 5; i++)
		{
			baseTurrets[i].setActive(false);
			baseTurrets[i].setDamage(1);
		}
		nebula.setX(0);
		nebula.setY(0);
		roundsLeft = 3;
		S1PerWave = 5;
		S2PerWave = 5;
		S3PerWave = 5;
		S4PerWave = 5;
		turretPoints = 10;
		roundStart = false;
		S1PerWaveMax = 5;
		S2PerWaveMax = 5;
		S3PerWaveMax = 5;
		S4PerWaveMax = 5;
		gameTimer = 0;
		wavesLeft = 12;
		EhealthMax = 1;
		if(input->isKeyDown(0x52)){
			gameState = RULES;
		}
		if(input->isKeyDown(0x31)){
			
			gameState = LVL1;
		}
		if(input->isKeyDown(0x32)){
			
			gameState = LVL2;
		}
		break;
	case LVL1:
		level1 = true;
		level2 = false;
		level3 = false;
		turretBases[0].setX(500);
		turretBases[0].setY(1000);
		turretBases[1].setX(700);
		turretBases[1].setY(700);
		turretBases[2].setX(900);
		turretBases[2].setY(500);
		turretBases[3].setX(1100);
		turretBases[3].setY(300);
		turretBases[4].setX(1300);
		turretBases[4].setY(100);
	
		spawners[0].setX(100);
		spawners[0].setY(200);
		spawners[1].setX(100);
		spawners[1].setY(700);
		spawners[2].setX(600);
		spawners[2].setY(100);
		spawners[3].setX(1000);
		spawners[3].setY(100);

		core.setX(1300);
		core.setY(900);
		gameState = GAMEPLAY;
		break;
	case LVL2:
		level1 = false;
		level2 = true;
		level3 = false;

		turretBases[0].setX(1000);
		turretBases[0].setY(800);
		turretBases[1].setX(500);
		turretBases[1].setY(800);
		turretBases[2].setX(400);
		turretBases[2].setY(500);
		turretBases[3].setX(800);
		turretBases[3].setY(300);
		turretBases[4].setX(1200);
		turretBases[4].setY(500);
	
		spawners[0].setX(BACK_WIDTH/2 - 32);
		spawners[0].setY(100);
		spawners[1].setX(100);
		spawners[1].setY(BACK_HEIGHT/2 - 32);
		spawners[2].setX(BACK_WIDTH/2 - 32);
		spawners[2].setY(BACK_HEIGHT - 100 - 32);
		spawners[3].setX(BACK_WIDTH - 100 - 32);
		spawners[3].setY(BACK_HEIGHT/2 - 32);

		core.setX(BACK_WIDTH/2 - 32);
		core.setY(BACK_HEIGHT/2 - 32);
		gameState = GAMEPLAY;
		break;
	case TRAN1:
		gameState = LVL2;
		break;
	case TRAN2:
		gameState = LVL3;
		break;
	case GAMEOVER:
		if (input->isKeyDown(VK_RETURN))
		{
			gameState = MENU;

		}
		break;
	case RULES:
		if(input->isKeyDown(VK_BACK)){
			gameState = MENU;
		}
		break;
	case PAUSE:
		if(input->isKeyDown(0x53)){
			//save
		}
		if(input->isKeyDown(VK_BACK)){
			gameState = GAMEPLAY;
		}
		if(input->isKeyDown(VK_ESCAPE)){
			exitGame();
		}
	}


}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{
	for(int i = 0; i < 50; i++){
		enemies[i].ai(frameTime,core);
	}
}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{
  VECTOR2 collisionVector;

  for(int i = 0; i < 50; i++){
	  if(core.collidesWith(enemies[i],collisionVector)){
		  core.setCoreHealthe(core.getCoreHealth() - 1);
		  red.setVisible(true);
		  enemies[i].setActive(false);
	  }
  }

	for(int i = 0; i < 50; i ++){
		for(int j = 0; j < 50; j++){
			if(missiles[i].collidesWith(enemies[j],collisionVector)){
				enemies[j]. setEnemyHealth(enemies[j].getEnemyHealth() - 1);
				missiles[i].setActive(false);
			}
	}
	}
	for(int i = 0; i < 50; i ++){
		for(int j = 0; j < 50; j++){
			if(turretMissiles1[i].collidesWith(enemies[j],collisionVector)){
				enemies[j]. setEnemyHealth(enemies[j].getEnemyHealth() - baseTurrets[0].getDamage());
				turretMissiles1[i].setActive(false);
			}
	}
	}
	for(int i = 0; i < 50; i ++){
		for(int j = 0; j < 50; j++){
			if(turretMissiles2[i].collidesWith(enemies[j],collisionVector)){
				enemies[j]. setEnemyHealth(enemies[j].getEnemyHealth() - baseTurrets[1].getDamage());
				turretMissiles2[i].setActive(false);
			}
	}
	}
	for(int i = 0; i < 50; i ++){
		for(int j = 0; j < 50; j++){
			if(turretMissiles3[i].collidesWith(enemies[j],collisionVector)){
				enemies[j]. setEnemyHealth(enemies[j].getEnemyHealth() - baseTurrets[2].getDamage());
				turretMissiles3[i].setActive(false);
			}
	}
	}
	for(int i = 0; i < 50; i ++){
		for(int j = 0; j < 50; j++){
			if(turretMissiles4[i].collidesWith(enemies[j],collisionVector)){
				enemies[j]. setEnemyHealth(enemies[j].getEnemyHealth() - baseTurrets[3].getDamage());
				turretMissiles4[i].setActive(false);
			}
	}
	}
	for(int i = 0; i < 50; i ++){
		for(int j = 0; j < 50; j++){
			if(turretMissiles5[i].collidesWith(enemies[j],collisionVector)){
				enemies[j]. setEnemyHealth(enemies[j].getEnemyHealth() - baseTurrets[4].getDamage());
				turretMissiles5[i].setActive(false);
			}
	}
	}
	for(int i = 0; i < 50; i++){
	if (baseTurrets[0].collidesWith(enemies[i],collisionVector) && turretTimer1 <= 0 )
	{
		turretAngle1 = atan2(enemies[i].getCenterY() - baseTurrets[0].getCenterY(), enemies[i].getCenterX() - baseTurrets[0].getCenterX());
		turretAngle1 *= (180/PI);
		baseTurrets[0].setDegrees(90 + turretAngle1);
		audio->playCue(FIRE);
		turretMissiles1[turretMissileIndex1].setDegrees(angle);
		turretMissiles1[turretMissileIndex1].setX(baseTurrets[0].getX());
		turretMissiles1[turretMissileIndex1].setY(baseTurrets[0].getY());
		VECTOR2 fVec(enemies[i].getCenterX() - baseTurrets[0].getCenterX(), enemies[i].getCenterY() - baseTurrets[0].getCenterY());
	 D3DXVec2Normalize(&fVec, &fVec); 
	 turretMissiles1[turretMissileIndex1].setVelocity(fVec);
	 turretMissiles1[turretMissileIndex1].activate();
	 turretMissileIndex1++;
	 turretTimer1 = turretMax;
	 
	 
			
	} 
		

		
	
	}
		for(int i = 0; i < 50; i++){
				if (baseTurrets[1].collidesWith(enemies[i],collisionVector) && turretTimer2 <= 0 )
	{
		turretAngle2 = atan2(enemies[i].getCenterY() - baseTurrets[1].getCenterY(), enemies[i].getCenterX() - baseTurrets[1].getCenterX());
		turretAngle2 *= (180/PI);
		baseTurrets[1].setDegrees(90 + turretAngle2);

		audio->playCue(FIRE);
		turretMissiles2[turretMissileIndex2].setDegrees(angle);
		turretMissiles2[turretMissileIndex2].setX(baseTurrets[1].getX());
		turretMissiles2[turretMissileIndex2].setY(baseTurrets[1].getY());
		VECTOR2 fVec(enemies[i].getCenterX() - baseTurrets[1].getCenterX(), enemies[i].getCenterY() - baseTurrets[1].getCenterY());
	 D3DXVec2Normalize(&fVec, &fVec); 
	 turretMissiles2[turretMissileIndex2].setVelocity(fVec);
	 turretMissiles2[turretMissileIndex2].activate();
	 turretMissileIndex2++;
	 turretTimer2 = turretMax;
	 
			
	} 
		

		
	
		}
		for(int i = 0; i < 50; i++){
				if (baseTurrets[2].collidesWith(enemies[i],collisionVector) && turretTimer3 <= 0 )
	{
		turretAngle3 = atan2(enemies[i].getCenterY() - baseTurrets[2].getCenterY(), enemies[i].getCenterX() - baseTurrets[2].getCenterX());
		turretAngle3 *= (180/PI);
		baseTurrets[2].setDegrees(90 + turretAngle3);
		audio->playCue(FIRE);
		turretMissiles3[turretMissileIndex3].setDegrees(angle);
		turretMissiles3[turretMissileIndex3].setX(baseTurrets[2].getX());
		turretMissiles3[turretMissileIndex3].setY(baseTurrets[2].getY());
		VECTOR2 fVec(enemies[i].getCenterX() - baseTurrets[2].getCenterX(), enemies[i].getCenterY() - baseTurrets[2].getCenterY());
	 D3DXVec2Normalize(&fVec, &fVec); 
	 turretMissiles3[turretMissileIndex3].setVelocity(fVec);
	 turretMissiles3[turretMissileIndex3].activate();
	 turretMissileIndex3++;
	 turretTimer3 = turretMax;
	 
			
	} 
		

		
	
		}
		for(int i = 0; i < 50; i++){
			if (baseTurrets[3].collidesWith(enemies[i],collisionVector) && turretTimer4 <= 0 )
	{
		turretAngle4 = atan2(enemies[i].getCenterY() - baseTurrets[3].getCenterY(), enemies[i].getCenterX() - baseTurrets[3].getCenterX());
		turretAngle4 *= (180/PI);
		baseTurrets[3].setDegrees(90 + turretAngle4);		
		audio->playCue(FIRE);
		turretMissiles4[turretMissileIndex4].setDegrees(angle);
		turretMissiles4[turretMissileIndex4].setX(baseTurrets[3].getX());
		turretMissiles4[turretMissileIndex4].setY(baseTurrets[3].getY());
		VECTOR2 fVec(enemies[i].getCenterX() - baseTurrets[3].getCenterX(), enemies[i].getCenterY() - baseTurrets[3].getCenterY());	
		D3DXVec2Normalize(&fVec, &fVec); 
	 turretMissiles4[turretMissileIndex4].setVelocity(fVec);
	 turretMissiles4[turretMissileIndex4].activate();
	 turretMissileIndex4++;
	 turretTimer4 = turretMax;
	 
			
	} 
		

		
	
		}
		for(int i = 0; i < 50; i++){
			if (baseTurrets[4].collidesWith(enemies[i],collisionVector) && turretTimer5 <= 0 )
	{
		turretAngle5 = atan2(enemies[i].getCenterY() - baseTurrets[4].getCenterY(), enemies[i].getCenterX() - baseTurrets[4].getCenterX());
		turretAngle5 *= (180/PI);
		baseTurrets[4].setDegrees(90 + turretAngle5);
		audio->playCue(FIRE);
		turretMissiles5[turretMissileIndex5].setDegrees(angle);
		turretMissiles5[turretMissileIndex5].setX(baseTurrets[4].getX());
		turretMissiles5[turretMissileIndex5].setY(baseTurrets[4].getY());
		VECTOR2 fVec(enemies[i].getCenterX() - baseTurrets[4].getCenterX(), enemies[i].getCenterY() - baseTurrets[4].getCenterY());
	 D3DXVec2Normalize(&fVec, &fVec); 
	 turretMissiles5[turretMissileIndex5].setVelocity(fVec);
	 turretMissiles5[turretMissileIndex5].activate();
	 turretMissileIndex5++;
	 turretTimer5 = turretMax;
	 
			
	} 
		

		
	
		}
	
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{

	std::stringstream ss;
	std::stringstream ss2;
	std::stringstream ss3;
	std::stringstream ss4;

	ss << score;
	ss2 << finalString;
	ss2 << score;
	//ss3 << "Turret Points: ";
	ss3 << turretPoints;
	output->setFontColor(graphicsNS::GREEN);
    graphics->spriteBegin(); // begin drawing sprites
	if(gameState == TITLESCREEN){
		splash.draw();
	}
	if(gameState == MENU){
		menu.draw();
	}
	if(gameState == GAMEPLAY){
	nebula.draw();                          // add the orion nebula to the scene
	health.draw(); 
	for( int i =0; i < 50; i++)
	{
	  
		  
		 if (missiles[i].getActive())
		{
			missiles[i].draw();
		}
		 if(turretMissiles1[i].getActive()){
			 turretMissiles1[i].draw();
		 }
		 if(turretMissiles2[i].getActive()){
			 turretMissiles2[i].draw();
		 }
		 if(turretMissiles2[i].getActive()){
			 turretMissiles2[i].draw();
		 }
		 if(turretMissiles3[i].getActive()){
			 turretMissiles3[i].draw();
		 }
		 if(turretMissiles4[i].getActive()){
			 turretMissiles4[i].draw();
		 }
		 if(turretMissiles5[i].getActive()){
			 turretMissiles5[i].draw();
		 }
	}

	if (!gamePlaying)
	{
		output->print(ss2.str(), 300,300);
	}
	for(int i = 0; i < 5; i++) {
		if(baseTurrets[i].getActive()) baseTurrets[i].draw();
	}
		for(int i = 0; i < 5; i++) {
			if(burstTurrets[i].getActive()) burstTurrets[i].draw();
	}
		for(int i = 0; i < 5; i++) {
			if(sniperTurrets[i].getActive()) sniperTurrets[i].draw();
	}
	for(int i = 0; i < 4; i++) {
		spawners[i].draw();
	}
	for(int i = 0; i < 50; i++){
		if(enemies[i].getActive()){
			enemies[i].draw();
		}
	}

		if (!roundStart)
	{
		begin.draw();
		info1.draw();
	}
	if(core.getActive()) core.draw();
	turret_selection.draw();
	output->print(ss.str(), 250,510);
	output->print(ss3.str(), 650,510);
	if(roundStart) arrow.draw();
	ship1.draw();
	}

	if (gameState == GAMEOVER)
	{
		nebula.draw();
		output->print(endString, 300,200);
		output->print(ss2.str(), 300,300);
		output->print("Press Enter to return to menu", 300,500);



	}
	if(gameState == PAUSE) pause.draw();
	if(gameState == RULES) rules.draw();
    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Spacewar::releaseAll()
{
    nebulaTexture.onLostDevice();
    gameTextures.onLostDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Spacewar::resetAll()
{
    gameTextures.onResetDevice();
    nebulaTexture.onResetDevice();
    Game::resetAll();
    return;
}

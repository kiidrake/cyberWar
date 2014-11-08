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
    if (!nebulaTexture.initialize(graphics,NEBULA_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

    // main game textures
    if (!gameTextures.initialize(graphics,SHIP_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));
	if (!snakeTexture.initialize(graphics,SNAKE_IMAGE))
		  throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing snake textures"));
    // nebula image
    if (!nebula.initialize(graphics,0,0,0,&nebulaTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));
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
    health.setFrames(healthNS::SHIP1_START_FRAME, healthNS::SHIP1_START_FRAME);
	health.setCurrentFrame(ship1.getShipHealth());
    health.setX(10);
    health.setY(10);
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

	outputHL->setFontColor(graphicsNS::RED);
	
	preGame = true;
    gamePlaying = true;
	score = 0;
	colCounter = 0;
	missileIndex= 0;
	
	fired = false;
	
	gameTimer = 0;
	increaseTime = 2.0;
	
	preGameTimer = 8.0;
	srand (time(NULL));
    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	//ROTATE SHIP WITH MOUSE USING CMATH FUNCTIONS
	angle = atan2(input->getMouseY() - ship1.getY(), input->getMouseX() - ship1.getX());
	angle *= (180/PI);
	ship1.setDegrees(90 + angle);

	if (ship1.getShipHealth() <= 0)
	{
		gamePlaying = false;																								
		audio->stopCue(BACKGROUND);

	}
    
	ship1.update(frameTime);
	gameTimer += frameTime;
	if (nebula.getX() <= 0 && ship1.getCenterX() >= (GAME_WIDTH/2) - 10 && ship1.getCenterX() <= (GAME_WIDTH/2) + 10  && nebula.getX()  >= (int)GAME_WIDTH - (int)BACK_WIDTH )
	{
		
		nebula.setX(nebula.getX() - frameTime * ship1.getVelocity().x);
	}
	
	else 
	{
		if (nebula.getX() > 0 )
		{
			nebula.setX(0);
		}
		if (nebula.getX() < ((int)GAME_WIDTH - (int)BACK_WIDTH) )
		{
			nebula.setX(((int)GAME_WIDTH - (int)BACK_WIDTH));
		}
		ship1.setX(ship1.getX() + frameTime * ship1.getVelocity().x);
	}
	
	if (nebula.getY() <= 0 && ship1.getCenterY() >= (GAME_HEIGHT/2) - 10 && ship1.getCenterY() <= (GAME_HEIGHT/2) + 10  && nebula.getY()  >= (int)GAME_HEIGHT - (int)BACK_HEIGHT )
	{
		
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
	
	
	if ((input->isKeyDown(VK_SPACE)) && !fired )
	{
		audio->playCue(SHOOT);
	 missiles[missileIndex].setX(ship1.getX());
	 missiles[missileIndex].setY(ship1.getY());
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
	
	
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Spacewar::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Spacewar::collisions()
{
  VECTOR2 collisionVector;

	
	
		
	
}

//=============================================================================
// Render game items
//=============================================================================
void Spacewar::render()
{
	std::stringstream ss;
	std::stringstream ss2;
	
	ss << outString;
	ss << score;
	ss2 << finalString;
	ss2 << score;
	
    graphics->spriteBegin();                // begin drawing sprites
	
	nebula.draw();                          // add the orion nebula to the scene
								  // add the planet to the scene
	health.draw();
	ship1.draw();  
	for( int i =0; i < 50; i++)
	{
	  
		  
		 if (missiles[i].getActive())
		{
			missiles[i].draw();
		}
	}
	output->print(ss.str(), 600,0);
	if (!gamePlaying)
	{
		output->print(ss2.str(), 300,300);
	}
		
	
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

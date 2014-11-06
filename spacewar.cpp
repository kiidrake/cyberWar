// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Draw animated spaceships with collision and shield
// Chapter 6 spacewar.cpp v1.0
// This class is the core of the game

#include "spaceWar.h"

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
    ship1.setX(GAME_WIDTH/4);
    ship1.setY(GAME_HEIGHT/4);
    ship1.setVelocity(VECTOR2(shipNS::SPEED,-shipNS::SPEED)); // VECTOR2(X, Y)
	ship1.setScale(ship1.getScale() * 2);
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
		if (!armadillos[i].initialize(this, armadilloNS::WIDTH, armadilloNS::HEIGHT, armadilloNS::TEXTURE_COLS, &armadilloTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing missile1"));
		 armadillos[i].setFrames(armadilloNS::SHIP1_START_FRAME, armadilloNS::SHIP1_END_FRAME);
		 armadillos[i].setCurrentFrame(armadilloNS::SHIP1_START_FRAME);
		 armadillos[i].setX(GAME_WIDTH/4);
		 armadillos[i].setY(GAME_HEIGHT/4);
		 armadillos[i].setVelocity(VECTOR2(armadilloNS::SPEED,-armadilloNS::SPEED)); // VECTOR2(X, Y)
	}


	for( int i =0; i < 50; i++)
	{
		 if (!snakes[i].initialize(this, snakeNS::WIDTH, snakeNS::HEIGHT, snakeNS::TEXTURE_COLS, &snakeTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing missile1"));
		 snakes[i].setFrames(snakeNS::SHIP1_START_FRAME, snakeNS::SHIP1_END_FRAME);
		 snakes[i].setCurrentFrame(snakeNS::SHIP1_START_FRAME);
		 snakes[i].setX(GAME_WIDTH/4);
		 snakes[i].setY(GAME_HEIGHT/4);
		 snakes[i].setVelocity(VECTOR2(snakeNS::SPEED,-snakeNS::SPEED)); // VECTOR2(X, Y)
	}

	for( int i =0; i < 50; i++)
	{
		if (!spiders[i].initialize(this, spiderNS::WIDTH, spiderNS::HEIGHT, spiderNS::TEXTURE_COLS, &spiderTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing missile1"));
		 spiders[i].setFrames(spiderNS::SHIP1_START_FRAME, spiderNS::SHIP1_END_FRAME);
		 spiders[i].setCurrentFrame(spiderNS::SHIP1_START_FRAME);
		 spiders[i].setX(GAME_WIDTH/4);
		 spiders[i].setY(GAME_HEIGHT/4);
		 spiders[i].setVelocity(VECTOR2(spiderNS::SPEED,-spiderNS::SPEED)); // VECTOR2(X, Y)
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
	swarmReady = false;
	preGame = true;
    gamePlaying = true;
	score = 0;
	colCounter = 0;
	missileIndex= 0;
	snakeIndex = 0;
	spiderIndex = 0;
	armadilloIndex =0;
	fired = false;
	maxArmadillo = 5.0;
	maxSpider = 8.0;
	maxSnake = 6.0;
	spawnArmadillo= false;
	spawnSnake = false;
	spawnSpider= false;
	gameTimer = 0;
	increaseTime = 2.0;
	armadilloTimer = maxArmadillo;
	snakeTimer = maxSnake;
	spiderTimer = maxSpider;
	swarmTimer = 20.0;
	preGameTimer = 8.0;
	srand (time(NULL));
    return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Spacewar::update()
{
	if (preGame)
	{
		preGameTimer-= frameTime;
		if (preGameTimer < 0)
		{
			preGame = false;
		}
	


	}
	if (gamePlaying && !preGame)
	{
		if (ship1.getShipHealth() <= 0)
		{
			gamePlaying = false;
			audio->stopCue(BACKGROUND);

		}
    
		ship1.update(frameTime);
		gameTimer += frameTime;
		armadilloTimer-= frameTime;
		spiderTimer -= frameTime;
		snakeTimer -= frameTime;
		swarmTimer -= frameTime;
		if (swarmTimer <= 0)
		{
			swarmReady = true;
			swarmTimer = 10.0;
		}
		if (armadilloTimer <= 0)
		{
			spawnArmadillo = true;
			armadilloTimer = maxArmadillo;
		}
		if (spiderTimer <= 0)
		{
			spawnSpider = true;
			spiderTimer = maxSpider;
		}
		if (snakeTimer <= 0)
		{
			spawnSnake = true;
			snakeTimer = maxSnake;
		}
		if (gameTimer >= increaseTime)
		{
			increaseTime += 12.0;
			maxArmadillo -= (maxArmadillo/10);
			maxSpider -= (maxSpider/20);
			maxSnake -= (maxSnake /12);
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

		if ((input->isKeyDown(VK_SHIFT)) && !swarmFired  )
		{
			if (swarmReady)
			{
			   audio->playCue(SHOOT);
			   missiles[missileIndex].setX(ship1.getX());
			   missiles[missileIndex].setY(ship1.getY());
			   missiles[missileIndex].activate();
			   missileIndex++;
			   if (missileIndex >=50)
				{
					missileIndex = 0;
				}
			   for (int i =1; i < 5; i++)
			   {
			     missiles[missileIndex].setX(ship1.getX());
			     missiles[missileIndex].setY(ship1.getY()+(10*i));
			     missiles[missileIndex].activate();
			     missileIndex++;
			   if (missileIndex >=50)
				{
					missileIndex = 0;
				}

			    missiles[missileIndex].setX(ship1.getX());
			    missiles[missileIndex].setY(ship1.getY()-(10*i));
			    missiles[missileIndex].activate();
			    missileIndex++;
			   }
			   swarmReady = false;
			   swarmTimer = 20.0;
			}
		swarmFired = true;
			
		} 
		else if ((input->isKeyDown(VK_SHIFT)) && swarmFired )
		{
    
		} 
		else
		{
			swarmFired = false;
		}



		if (spawnArmadillo )
		{
		 spawnLoc = rand() % 19 + 1;
		 armadillos[armadilloIndex].setX(GAME_WIDTH);
		 armadillos[armadilloIndex].setY(spawnLoc * GAME_HEIGHT/20);
		 armadillos[armadilloIndex].activate();
		 armadilloIndex++;
		 spawnArmadillo = false;
		} 
	

		if (spawnSnake )
		{
		 spawnLoc = rand() % 4 + 1;
		 snakes[snakeIndex].setX(GAME_WIDTH);
		 snakes[snakeIndex].setY(spawnLoc * GAME_HEIGHT/5);
	     snakes[snakeIndex].activate();
		 snakeIndex++;
		 spawnSnake = false;;
		} 
	

		if (spawnSpider )
		{
		 spawnLoc = rand() % 3 + 1;
		 spiders[spiderIndex].setX(GAME_WIDTH);
		 spiders[spiderIndex].setY(spawnLoc *GAME_HEIGHT/4);
	     spiders[spiderIndex].activate();
		 spiderIndex++;
		 spawnSpider = false;
		} 
	
		for( int i =0; i < 50; i++)
		{
		
		  armadillos[i].update(frameTime);
		  snakes[i].update(frameTime);
		  spiders[i].update(frameTime);
		  missiles[i].update(frameTime);
		}
	
		if (missileIndex >=50)
		{
			missileIndex = 0;
		}
		if (armadilloIndex == 50)
		{
			armadilloIndex = 0;
		}
		if (spiderIndex == 50)
		{
			spiderIndex = 0;
		}
		if (snakeIndex == 50)
		{
			snakeIndex = 0;
		}
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

	for(int i = 0; i < 50;i++){
		for(int j = 0; j < 50; j++){
			if(missiles[i].collidesWith(armadillos[j],collisionVector)){
				audio->playCue(HIT);
				armadillos[j].setActive(false);
				missiles[i].setActive(false);
				score += 200;
			}
		}
	} 
	for(int i = 0; i < 50;i++){
		for(int j = 0; j < 50; j++){
			if(missiles[i].collidesWith(snakes[j],collisionVector)){
				audio->playCue(HIT);
				snakes[j].setActive(false);
				missiles[i].setActive(false);
				score += 300;
			}
		}
	}
		for(int i = 0; i < 50;i++){
		for(int j = 0; j < 50; j++){
			if(missiles[i].collidesWith(spiders[j],collisionVector)){
				audio->playCue(HIT);
				spiders[j].setActive(false);
				missiles[i].setActive(false);
				score += 500;
			}
		}
	}
		for(int i = 0;i < 50; i++){
			if(ship1.collidesWith(armadillos[i],collisionVector)){
				audio->playCue(DAMAGE);
				armadillos[i].setActive(false);
				ship1.damage();
				health.setCurrentFrame(ship1.getShipHealth());
			}
			if(ship1.collidesWith(snakes[i],collisionVector)){
				audio->playCue(DAMAGE);
				snakes[i].setActive(false);
				ship1.damage();
				health.setCurrentFrame(ship1.getShipHealth());
			}
			if(ship1.collidesWith(spiders[i],collisionVector)){
				audio->playCue(DAMAGE);
				spiders[i].setActive(false);
				ship1.damage();
				health.setCurrentFrame(ship1.getShipHealth());
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
	
	ss << outString;
	ss << score;
	ss2 << finalString;
	ss2 << score;
	
    graphics->spriteBegin();                // begin drawing sprites
	if (preGame)
	{
		output->print(introString1, 20,100);
		outputHL->print(introString2, 20,200);
		output->print(introString3, 20,300);
	}
	else
	{
		nebula.draw();                          // add the orion nebula to the scene
								  // add the planet to the scene
		health.draw();
		ship1.draw();  
		for( int i =0; i < 50; i++)
		{
	  
		   if (armadillos[i].getActive())
			{
				armadillos[i].draw();
			}
			if (snakes[i].getActive())
			{
				snakes[i].draw();
			}
			 if (spiders[i].getActive())
			{
				spiders[i].draw();
			}
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
		if (swarmReady)
		{
			output->print(swarmString, 200,0);
		}
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

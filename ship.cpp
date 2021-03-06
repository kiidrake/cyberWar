// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.cpp v1.0

#include "ship.h"

//=============================================================================
// default constructor
//=============================================================================
Ship::Ship() : Entity()
{
    spriteData.width = shipNS::WIDTH;           // size of Ship1
    spriteData.height = shipNS::HEIGHT;
    spriteData.x = shipNS::X;                   // location on screen
    spriteData.y = shipNS::Y;
    spriteData.rect.bottom = shipNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = shipNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = shipNS::SHIP_ANIMATION_DELAY;
    startFrame = shipNS::SHIP1_START_FRAME;     // first frame of ship animation
    endFrame     = shipNS::SHIP1_END_FRAME;     // last frame of ship animation
    currentFrame = startFrame;
    radius = shipNS::WIDTH/2.0;
    shieldOn = false;
    mass = shipNS::MASS;
    collisionType = entityNS::CIRCLE;
	shipHealth = 5;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool Ship::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    shield.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
    shield.setFrames(shipNS::SHIELD_START_FRAME, shipNS::SHIELD_END_FRAME);
    shield.setCurrentFrame(shipNS::SHIELD_START_FRAME);
    shield.setFrameDelay(shipNS::SHIELD_ANIMATION_DELAY);
    shield.setLoop(false);                  // do not loop animation
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// draw the ship
//=============================================================================
void Ship::draw()
{
    Image::draw();              // draw ship
    if(shieldOn)
        // draw shield using colorFilter 50% alpha
        shield.draw(spriteData, graphicsNS::ALPHA50 & colorFilter);
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Ship::update(float frameTime)
{
    Entity::update(frameTime);
	velocity.x = shipNS::SPEED;
	velocity.y = shipNS::SPEED;
	//if (input->isKeyDown(0x44) || input->isKeyDown(VK_RIGHT))
	//{
 //   velocity.x = shipNS::SPEED ;
	//}   
	//
	//if (input->isKeyDown(0x41)|| input->isKeyDown(VK_LEFT))
	//{
 //    velocity.x = -shipNS::SPEED ;
	//} 
	//if (input->isKeyDown(0x57)|| input->isKeyDown(VK_UP))
	//{
 //    velocity.y = -shipNS::SPEED ;
	//}
	//if (input->isKeyDown(0x53)|| input->isKeyDown(VK_DOWN))
	//{
 //    velocity.y = shipNS::SPEED ;  
	//} 
	// move ship 
         
    // Bounce off walls
	/*
    if (spriteData.x > GAME_WIDTH-shipNS::WIDTH)    // if hit right screen edge
    {
        spriteData.x = GAME_WIDTH-shipNS::WIDTH;    // position at right screen edge
                           // reverse X direction
    } else if (spriteData.x < 0)                    // else if hit left screen edge
    {
        spriteData.x = 0;                           // position at left screen edge
                           // reverse X direction
    }
    if (spriteData.y > GAME_HEIGHT-shipNS::HEIGHT)  // if hit bottom screen edge
    {
        spriteData.y = GAME_HEIGHT-shipNS::HEIGHT;  // position at bottom screen edge
                           // reverse Y direction
    } else if (spriteData.y < 0)                    // else if hit top screen edge
    {
        spriteData.y = 0;                           // position at top screen edge
                           // reverse Y direction
    }
	*/
    if(shieldOn)
    {
        shield.update(frameTime);
        if(shield.getAnimationComplete())
        {
            shieldOn = false;
            shield.setAnimationComplete(false);
        }
    }
}

//=============================================================================
// damage
//=============================================================================
void Ship::damage()
{
    shipHealth--;
}

int Ship::getShipHealth()
{
	return shipHealth;
}
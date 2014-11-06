#include "missile.h"


Missile::Missile() : Entity()
{
    spriteData.width = missileNS::WIDTH;           // size of Ship1
    spriteData.height = missileNS::HEIGHT;
    spriteData.x = missileNS::X;                   // location on screen
    spriteData.y = missileNS::Y;
    spriteData.rect.bottom = missileNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = missileNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = missileNS::SHIP_ANIMATION_DELAY;
    startFrame = missileNS::SHIP1_START_FRAME;     // first frame of ship animation
    endFrame     = missileNS::SHIP1_END_FRAME;     // last frame of ship animation
    currentFrame = startFrame;
    radius = missileNS::WIDTH/16.0;
    active = false;
    mass = missileNS::MASS;
    collisionType = entityNS::CIRCLE;
}


bool Missile::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Missile::draw()
{
    Image::draw();              // draw ship
    
}


void Missile::update(float frameTime)
{
    Entity::update(frameTime);
    
	
	if ( active)
	{
    spriteData.x += frameTime * velocity.x;  
	} 

	




    // Bounce off walls
    if ((spriteData.x > GAME_WIDTH-missileNS::WIDTH)   && active)    // if hit right screen edge
    {
		active = false;
        spriteData.x = GAME_WIDTH-missileNS::WIDTH;    // position at right screen edge
                           // reverse X direction
    } 
   
}


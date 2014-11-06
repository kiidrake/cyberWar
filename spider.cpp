#include "spider.h"


Spider::Spider() : Entity()
{
    spriteData.width = spiderNS::WIDTH;           // size of Ship1
    spriteData.height = spiderNS::HEIGHT;
    spriteData.x = spiderNS::X;                   // location on screen
    spriteData.y = spiderNS::Y;
    spriteData.rect.bottom = spiderNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = spiderNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = spiderNS::SHIP_ANIMATION_DELAY;
    startFrame = spiderNS::SHIP1_START_FRAME;     // first frame of ship animation
    endFrame     = spiderNS::SHIP1_END_FRAME;     // last frame of ship animation
    currentFrame = startFrame;
    radius = spiderNS::WIDTH/8.0;
    active = false;
    mass = spiderNS::MASS;
    collisionType = entityNS::CIRCLE;
	damaged = false;
	directionTime = 0.0;
}


bool Spider::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Spider::draw()
{
    Image::draw();              // draw ship
    
}


void Spider::update(float frameTime)
{
    Entity::update(frameTime);
    
	if (active)
	{
		directionTime += frameTime;

	}
	if ( active && (directionTime <= 1.5))
	{
    spriteData.x -= frameTime * velocity.x;  
    spriteData.y += frameTime * velocity.y; 

	} 
	else if ( active && (directionTime > 1.5) && (directionTime <= 3.0))
	{
	spriteData.x -= frameTime * velocity.x;  

	} 
	else if ( active && (directionTime > 3.0) && (directionTime <= 4.5))
	{
    spriteData.y += frameTime * velocity.y;
	spriteData.x += frameTime * velocity.x; 
	} 
	else if ( active && (directionTime > 4.5) && (directionTime <= 6.0))
	{
    spriteData.y -= frameTime * velocity.y; 
	spriteData.x += frameTime * velocity.x; 
	} 
	else if ( active && (directionTime > 6.0) && (directionTime <= 7.5))
	{
    spriteData.y -= frameTime * velocity.y;  
	spriteData.x -= frameTime * velocity.x; 

	} 
	else
	{
	 spriteData.x -= frameTime * velocity.x; 
	 spriteData.y += frameTime * velocity.y;  

	}
	




    // Bounce off walls
    if ((spriteData.x < 0)   && active)    // if hit right screen edge
    {
		active = false;
		directionTime = 0;
        spriteData.x = 0;    // position at right screen edge
                           // reverse X direction
    } 
    if (spriteData.y > GAME_HEIGHT-spiderNS::HEIGHT)  // if hit bottom screen edge
    {
        spriteData.y = GAME_HEIGHT-spiderNS::HEIGHT;  // position at bottom screen edge
        velocity.y = -velocity.y;                   // reverse Y direction
    } else if (spriteData.y < 0)                    // else if hit top screen edge
    {
        spriteData.y = 0;                           // position at top screen edge
        velocity.y = -velocity.y;                   // reverse Y direction
    }
}

void Spider::damage()
{
	if (!damaged)
	{
		damaged = true;
	}
	else
	{
		active = false;
		damaged = false;
	}
}

bool Spider::getDamage()
{
  return damaged;

}

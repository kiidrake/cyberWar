#include "snake.h"


Snake::Snake() : Entity()
{
    spriteData.width = snakeNS::WIDTH;           // size of Ship1
    spriteData.height = snakeNS::HEIGHT;
    spriteData.x = snakeNS::X;                   // location on screen
    spriteData.y = snakeNS::Y;
    spriteData.rect.bottom = snakeNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = snakeNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = snakeNS::SHIP_ANIMATION_DELAY;
    startFrame = snakeNS::SHIP1_START_FRAME;     // first frame of ship animation
    endFrame     = snakeNS::SHIP1_END_FRAME;     // last frame of ship animation
    currentFrame = startFrame;
    radius = snakeNS::WIDTH/4.0;
    active = false;
    mass = snakeNS::MASS;
    collisionType = entityNS::CIRCLE;
	damaged = false;
	directionTime = 0.75;
}


bool Snake::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Snake::draw()
{
    Image::draw();              // draw ship
    
}


void Snake::update(float frameTime)
{
    Entity::update(frameTime);
	
    

	
	
	if ( active)
	{
    spriteData.x -= frameTime * velocity.x; 
	spriteData.y += frameTime * velocity.y;
	directionTime -= frameTime;
	} 

	if (directionTime <= 0)
	{
		velocity.y *= -1;
		directionTime = 1.5;
	}




    // Bounce off walls
    if ((spriteData.x < 0)   && active)    // if hit right screen edge
    {
		active = false;
		directionTime = 0.75;
        spriteData.x = 0;    // position at right screen edge
                           // reverse X direction
    } 
   
}

void Snake::damage()
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

bool Snake::getDamage()
{
  return damaged;

}
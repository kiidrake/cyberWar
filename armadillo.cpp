#include "armadillo.h"


Armadillo::Armadillo() : Entity()
{
    spriteData.width = armadilloNS::WIDTH;           // size of Ship1
    spriteData.height = armadilloNS::HEIGHT;
    spriteData.x = armadilloNS::X;                   // location on screen
    spriteData.y = armadilloNS::Y;
    spriteData.rect.bottom = armadilloNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = armadilloNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = armadilloNS::SHIP_ANIMATION_DELAY;
    startFrame = armadilloNS::SHIP1_START_FRAME;     // first frame of ship animation
    endFrame     = armadilloNS::SHIP1_END_FRAME;     // last frame of ship animation
    currentFrame = startFrame;              
    radius = armadilloNS::WIDTH/4.0;
    active = false;
    mass = armadilloNS::MASS;
    collisionType = entityNS::CIRCLE;
	damaged = false;
}


bool Armadillo::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Armadillo::draw()
{
    Image::draw();              // draw ship
    
}


void Armadillo::update(float frameTime)
{
    Entity::update(frameTime);
   
}

void Armadillo::damage()
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

bool Armadillo::getDamage()
{
  return damaged;

}
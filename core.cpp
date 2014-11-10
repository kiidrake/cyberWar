#include "core.h"


Core::Core() : Entity()
{
    spriteData.width = CoreNS::WIDTH;           // size of Ship1
    spriteData.height = CoreNS::HEIGHT;
    spriteData.x = CoreNS::X;                   // location on screen
    spriteData.y = CoreNS::Y;
    spriteData.rect.bottom = CoreNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = CoreNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = CoreNS::SHIP_ANIMATION_DELAY;
    startFrame = CoreNS::SHIP1_START_FRAME;     // first frame of ship animation
    endFrame     = CoreNS::SHIP1_END_FRAME;     // last frame of ship animation
    currentFrame = startFrame;              
    radius = CoreNS::WIDTH/2;
    active = false;
    mass = CoreNS::MASS;
    collisionType = entityNS::CIRCLE;
	damaged = false;
	coreHealth = 10;
}


bool Core::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Core::draw()
{
    Image::draw();              // draw ship
    
}


void Core::update(float frameTime)
{
    Entity::update(frameTime);
   
}

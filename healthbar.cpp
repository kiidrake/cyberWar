#include "healthbar.h"


Health::Health() : Entity()
{
    spriteData.width = healthNS::WIDTH;           // size of Ship1
    spriteData.height = healthNS::HEIGHT;
    spriteData.x = healthNS::X;                   // location on screen
    spriteData.y = healthNS::Y;
    spriteData.rect.bottom = healthNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = healthNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = healthNS::SHIP_ANIMATION_DELAY;
    startFrame = healthNS::SHIP1_START_FRAME;     // first frame of ship animation
    currentFrame = startFrame;
    radius = healthNS::WIDTH/2.0;
    active = false;
    mass = healthNS::MASS;
    collisionType = entityNS::CIRCLE;
}


bool Health::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Health::draw()
{
    Image::draw();              // draw ship
    
}


void Health::update(float frameTime)
{
    Entity::update(frameTime);
  





}

void Health::damage(WEAPON weapon)
{}
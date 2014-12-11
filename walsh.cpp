#include "walsh.h"


BurstTurret::BurstTurret() : Entity()
{
    spriteData.width = BurstTurretNS::WIDTH;           // size of Ship1
    spriteData.height = BurstTurretNS::HEIGHT;
    spriteData.x = BurstTurretNS::X;                   // location on screen
    spriteData.y = BurstTurretNS::Y;
    spriteData.rect.bottom = BurstTurretNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = BurstTurretNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    currentFrame = startFrame;              
    radius = 250;
    active = false;
	damage = 1;

}


bool BurstTurret::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void BurstTurret::draw()
{
    Image::draw();              // draw ship
    
}

void BurstTurret::update(float frameTime)
{
    Entity::update(frameTime);

}

#include "BaseTurret.h"


BaseTurret::BaseTurret() : Entity()
{
    spriteData.width = BaseTurretNS::WIDTH;           // size of Ship1
    spriteData.height = BaseTurretNS::HEIGHT;
    spriteData.x = BaseTurretNS::X;                   // location on screen
    spriteData.y = BaseTurretNS::Y;
    spriteData.rect.bottom = BaseTurretNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = BaseTurretNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    currentFrame = startFrame;              
    radius = 250;
    active = false;
	damage = 1;

}


bool BaseTurret::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void BaseTurret::draw()
{
    Image::draw();              // draw ship
    
}

void BaseTurret::update(float frameTime)
{
    Entity::update(frameTime);

}

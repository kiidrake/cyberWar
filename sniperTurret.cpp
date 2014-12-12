#include "sniperTurret.h"


SniperTurret::SniperTurret() : Entity()
{
    spriteData.width = SniperTurretNS::WIDTH;           // size of Ship1
    spriteData.height = SniperTurretNS::HEIGHT;
    spriteData.x = SniperTurretNS::X;                   // location on screen
    spriteData.y = SniperTurretNS::Y;
    spriteData.rect.bottom = SniperTurretNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = SniperTurretNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    currentFrame = startFrame;              
    radius = 500;
    active = false;
	damage = 1;

}


bool SniperTurret::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void SniperTurret::draw()
{
    Image::draw();              // draw ship
    
}

void SniperTurret::update(float frameTime)
{
    Entity::update(frameTime);

}

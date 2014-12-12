#include "kloss.h"


TriTurret::TriTurret() : Entity()
{
    spriteData.width = TriTurretNS::WIDTH;           // size of Ship1
    spriteData.height = TriTurretNS::HEIGHT;
    spriteData.x = TriTurretNS::X;                   // location on screen
    spriteData.y = TriTurretNS::Y;
    spriteData.rect.bottom = TriTurretNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = TriTurretNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    currentFrame = startFrame;              
    radius = 250;
    active = false;
	damage = 1;

}


bool TriTurret::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void TriTurret::draw()
{
    Image::draw();              // draw ship
    
}

void TriTurret::update(float frameTime)
{
    Entity::update(frameTime);

}

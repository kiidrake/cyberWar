#include "enemySpawner.h"

EnemySpawner::EnemySpawner() : Entity()
{
    spriteData.width = enemySPawnerNS::WIDTH;           // size of Ship1
    spriteData.height = enemySPawnerNS::HEIGHT;
    spriteData.x = enemySPawnerNS::X;                   // location on screen
    spriteData.y = enemySPawnerNS::Y;
    spriteData.rect.bottom = enemySPawnerNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = enemySPawnerNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = enemySPawnerNS::SHIP_ANIMATION_DELAY;
    startFrame = enemySPawnerNS::SHIP1_START_FRAME;     // first frame of ship animation
    endFrame     = enemySPawnerNS::SHIP1_END_FRAME;     // last frame of ship animation
    currentFrame = startFrame;
    radius = enemySPawnerNS::WIDTH/8.0;
    active = false;
    mass = enemySPawnerNS::MASS;
    collisionType = entityNS::CIRCLE;
	damaged = false;
	directionTime = 0.0;
}


bool EnemySpawner::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void EnemySpawner::draw()
{
    Image::draw();              // draw ship
    
}


void EnemySpawner::update(float frameTime)
{




}
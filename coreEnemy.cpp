#include "coreEnemy.h"


coreEnemy::coreEnemy() : Entity()
{
    spriteData.width = coreEnemyNS::WIDTH;           // size of Ship1
    spriteData.height = coreEnemyNS::HEIGHT;
    spriteData.x = coreEnemyNS::X;                   // location on screen
    spriteData.y = coreEnemyNS::Y;
    spriteData.rect.bottom = coreEnemyNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = coreEnemyNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    frameDelay = coreEnemyNS::SHIP_ANIMATION_DELAY;
    startFrame = coreEnemyNS::SHIP1_START_FRAME;     // first frame of ship animation
    endFrame     = coreEnemyNS::SHIP1_END_FRAME;     // last frame of ship animation
    currentFrame = startFrame;              
    radius = coreEnemyNS::WIDTH/4.0;
    active = false;
    mass = coreEnemyNS::MASS;
    collisionType = entityNS::CIRCLE;
	damaged = false;
	patternStepIndex = 0;
}


bool coreEnemy::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void coreEnemy::draw()
{
    Image::draw();              // draw ship
    
}


void coreEnemy::update(float frameTime)
{
    Entity::update(frameTime);
    
	
	if ( active)
	{
		patternTime[patternStepIndex] -= frameTime;
	    if (patternTime[patternStepIndex] <= 0)
	    {
			patternStepIndex += 1;
	
	    }
		switch (patternSteps[patternStepIndex])
		{
		case NONE:
			break;
		case UP:
			setVelocity(D3DXVECTOR2(0, -1));
			break;
		case DOWN:
			setVelocity(D3DXVECTOR2(0, 1));
			break;
		case RIGHT:
			setVelocity(D3DXVECTOR2(1,0));
			break;
		case LEFT:
			setVelocity(D3DXVECTOR2(-1,0));
			break;
		case TRACK:
			vectorTrack();
			break;
		case UPLEFT:
			setVelocity(D3DXVECTOR2(-1,-1));
			break;
		case UPRIGHT:
			setVelocity(D3DXVECTOR2(1,-1));
			break;
		case DOWNLEFT:
			setVelocity(D3DXVECTOR2(-1,1));
			break;
		case DOWNRIGHT:
			setVelocity(D3DXVECTOR2(1,1));
			break;
		}
		D3DXVec2Normalize(&velocity, &velocity);
		spriteData.x += frameTime * velocity.x * coreEnemyNS::SPEED;  
		spriteData.y += frameTime * velocity.y * coreEnemyNS::SPEED;
		
		
	} 

	




    // Bounce off walls
    if ((spriteData.x < 0)   && active)    // if hit right screen edge
    {
		active = false;
        spriteData.x = 0;    // position at right screen edge
                           // reverse X direction
    } 
   
}

void coreEnemy::damage()
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

bool coreEnemy::getDamage()
{
  return damaged;

}

void coreEnemy::vectorTrack()
{
	VECTOR2 target = *targetEntity.getCenter();
	target -= *getCenter();
	D3DXVec2Normalize(&target,&target);
	setVelocity(target);
	//add code here
}

void coreEnemy::ai(float time, Entity &t)
{ 
	targetEntity = t;
	if (track)
	{
	vectorTrack();
	}
	//deltaTrack();
	//evade();
	return;
}

void coreEnemy::setPattern(PATTERN_STEP_ACTION first,PATTERN_STEP_ACTION second,PATTERN_STEP_ACTION third,PATTERN_STEP_ACTION fourth)
{
	patternSteps[0] = first;
	patternSteps[1] = second;
	patternSteps[2] = third;
	patternSteps[3] = fourth;
}

void coreEnemy::setPatternTime(float first, float second, float third, float fourth)
{
	patternTime[0] =first;
	patternTime[1] =second;
	patternTime[2] =third;
	patternTime[3] =fourth;
}
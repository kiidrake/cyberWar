#ifndef _CORE_ENEMY_H                 // Prevent multiple definitions if this 
#define _CORE_ENEMY_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN


#include "entity.h"
#include "constants.h"


namespace coreEnemyNS
{
    const int WIDTH = 64;                   // image width
    const int HEIGHT = 64;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float ROTATION_RATE = (float)PI; // radians per second
    const float SPEED = 200;                // 100 pixels per second
    const float MASS = 300.0f;              // mass
    const int   TEXTURE_COLS = 2;           // texture has 8 columns
    const int   SHIP1_START_FRAME = 0;      // ship1 starts at frame 0
    const int   SHIP1_END_FRAME = 1;        // ship1 animation frames 0,1,2,3
    const int   SHIP2_START_FRAME = 8;      // ship2 starts at frame 8
    const int   SHIP2_END_FRAME = 11;       // ship2 animation frames 8,9,10,11
    const float SHIP_ANIMATION_DELAY = 0.2f;    // time between frames
    const int   SHIELD_START_FRAME = 24;    // shield start frame
    const int   SHIELD_END_FRAME = 27;      // shield end frame
    const float SHIELD_ANIMATION_DELAY = 0.1f; // time between frames
}


class coreEnemy : public Entity
{
private:
	int enemyHealth;
    bool    damaged;
    Entity targetEntity;
	bool track;
	PATTERN_STEP_ACTION patternSteps[5];
	float patternTime[5];
	int patternStepIndex;
public:
    // constructor
    coreEnemy();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);
    void damage();
	
	void ai(float time, Entity &t);
	void vectorTrack();
	bool getDamage();
	void setPattern(PATTERN_STEP_ACTION,PATTERN_STEP_ACTION,PATTERN_STEP_ACTION,PATTERN_STEP_ACTION);
	void setPatternTime(float, float, float, float);
	int getEnemyHealth() { return enemyHealth;}
	void setEnemyHealth( int newHealth) { enemyHealth = newHealth;}
};
#endif
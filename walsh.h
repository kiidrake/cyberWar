#ifndef _WALSH_H                 // Prevent multiple definitions if this 
#define _WALSH_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace BurstTurretNS
{
    const int WIDTH = 64;                   // image width
    const int HEIGHT = 64;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
	    const int   TEXTURE_COLS = 3;           // texture has 8 columns
    const int   SHIP1_START_FRAME = 0;      // ship1 starts at frame 0
    const int   SHIP1_END_FRAME = 2;        // ship1 animation frames 0,1,2,3
	 const float SHIP_ANIMATION_DELAY = 0.1f;    // time between frame
}

// inherits from Entity class
class BurstTurret : public Entity
{
private:
	int health;
	bool mouseActive;
	bool done;
	int damage;
public:
    // constructor
    BurstTurret();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);
	int getHealth();
	bool getMouseActive();
	void setMouseActive(bool);
	void shoot();
	bool getDone() {return done;}
	void setDone(bool val) {done = val;}
	int getDamage() { return damage;}
	void setDamage( int newDamage) { damage = newDamage;}
};
#endif


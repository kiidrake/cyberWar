#ifndef _HEALTHBAR_H                 // Prevent multiple definitions if this 
#define _HEALTHBAR_H                  // file is included in more than one place
#define WIN32_LEAN_AND_MEAN


#include "entity.h"
#include "constants.h"

namespace healthNS
{
    const int WIDTH = 32;                   // image width
    const int HEIGHT = 32;                  // image height
    const int X = 1;   // location on screen
    const int Y = 1;
    const float ROTATION_RATE = (float)PI/4; // radians per second
    const float SPEED = 100;                // 100 pixels per second
    const float MASS = 300.0f;              // mass
    const int   TEXTURE_COLS = 6;           // texture has 8 columns
    const int   SHIP1_START_FRAME = 0;      // ship1 starts at frame 0
    const float SHIP_ANIMATION_DELAY = 0.2f;    // time between frames
    const int   SHIELD_START_FRAME = 24;    // shield start frame
    const int   SHIELD_END_FRAME = 27;      // shield end frame
    const float SHIELD_ANIMATION_DELAY = 0.1f; // time between frames
}


class Health : public Entity
{
private:
    bool    fired;
    Image   shield;
public:
    // constructor
    Health();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);
    void damage(WEAPON);
};
#endif
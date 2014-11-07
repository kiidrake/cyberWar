#ifndef _LOWTURRET_H                 // Prevent multiple definitions if this 
#define _LOWTURRET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace lowTurretNS
{
    const int WIDTH = 32;                   // image width
    const int HEIGHT = 32;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;

}

// inherits from Entity class
class lowTurret : public Entity
{
private:
	int health;
	bool mouseActive;
public:
    // constructor
    lowTurret();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);
	int getHealth();
	bool getMouseActive();
	void setMouseActive(bool);
	void shoot();
};
#endif


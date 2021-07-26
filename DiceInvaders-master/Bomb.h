#ifndef BOMB_H
#define BOMB_H

#include "Engine.h"

#ifdef VECTOR

#include <vector>

#else

#define MAX_BOMB 16

typedef struct  
{
	int size;	
	int x[MAX_BOMB];
	int y[MAX_BOMB];
}posB;

#endif

class Bomb {

private:
	Engine *engine;
	
public:
	/* Data structure to store all bombs fired randomly from Aliens */
	
#ifdef VECTOR
	std::vector<std::pair<int, int>> bomb_loc_vect;
#else
	posB bomb_loc_vect;
	
	void remove(int loc);
#endif

	//Default constructor
	Bomb(Engine *e);

	/* Draw bomb sprite on screen */
	void draw_bomb(int loc_x, int loc_y);
	
	/* Update bomb's co-ordinates */
	void update_bomb_position();
	
}__attribute__((aligned));

#endif

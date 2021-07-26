#ifndef ROCKETS_H
#define ROCKETS_H

#include "Engine.h"

#ifdef VECTOR

#include <vector>

#else

#define MAX_ROCKETS 32

typedef struct  
{
	int size;	
	int x[MAX_ROCKETS];
	int y[MAX_ROCKETS];
}posR;

#endif

	
class Rocket {

private:
	Engine *engine;
	
public:
	Rocket(Engine *e); //default constructor

	/* Data structure to store all rockets fired from Player */
#ifdef VECTOR
	std::vector<std::pair<int, int>> rocket_loc_vect;
#else
	posR rocket_loc_vect;
	
	void remove(int loc);
#endif

	/* To draw rocket Sprite on Canvas and store the location co-ordinates in the Vector data structure */
	void draw_rocket(int loc_x, int loc_y);
	
	/* To update the location co-ordinates in Vector data structure */
	void update_rocket_position();
	
}__attribute__((aligned));

#endif

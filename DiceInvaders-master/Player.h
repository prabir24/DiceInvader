#ifndef PLAYER_H
#define PLAYER_H

#include <cstring>
#include <string>
#include "Engine.h"
#include "Bomb.h"

class Player {

private:
	Engine *engine;
	
public:
	int score;
	int life;

	//Default constructor
	Player(Engine *e);	

	/* Update player location based on input's from user */
	void update_player_location(int loc_x);

	/* Fire rockets from current location of Player */
	void fire_rockets();

	/* Update score after aliens are killed by Player's rocket */ 
	void update_score();

	/* Display score on screen */
	void display_score();

	/* Update player life if bombed */
	void update_player_life(Bomb *b, int loc_x);

	/* Display life on screen */
	void display_life();
	
}__attribute__((aligned));

#endif

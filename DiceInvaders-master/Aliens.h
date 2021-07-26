#ifndef ALIENS_H
#define ALIENS_H

#include "Engine.h"
#include "Bomb.h"
#include "Rocket.h"
#include "Player.h"

#ifdef VECTOR

#include <vector>

#else

#define MAX_ALIEN 128

typedef struct  
{
	int size;
	int x[MAX_ALIEN];
	int y[MAX_ALIEN];
	Engine::Sprite al[MAX_ALIEN];
}posA;

#endif

class Aliens {

private:
	Bomb *bomb;
	Engine *engine;
	int alien_army_N_row;	//No. of rows in Alien army
	int alien_army_N_col;	//No. of columns in Alien army

	/* Boolean variable to check if Alien army has to move left or right */
	bool is_left_direction;
	
public:
	/* Boolean variable to check if Alien army direction has changed from left to right or vice-versa or not */
	bool has_direction_changed;

	/* Boolean variable to check if any of alien army has reached the bottom of screen */
	bool has_reached_bottom;

	/* Boolean variable to check if all aliens in the army have been killed or not */
	bool all_aliens_killed;
	
	/* Data structure to store alien army type and co-ordinates */
#ifdef VECTOR
	std::vector<std::pair<Engine::Sprite, std::pair<int, int>>> aliens_army_vect;
#else
	posA aliens_army_vect;
	
	void remove(int loc);
#endif

	//Default constructor
	Aliens(Engine *e, Bomb *b); 

	/* To draw the alien army on screen starting from top left corner */
	void draw_alien_army(int row, int col);
	
	/* To update the alien army co-ordinates while moving horizontally */
	void update_alien_army_horizontal();

	/* To update the alien army co-ordinates while moving downwards */	
	void update_alien_army_vertical();

	/* To refresh the alien army Sprite on screen */	
	void refresh_alien_army();
	
	/* To check if alien army has reached bottom of the screen */
	void reached_bottom();
	
	/* To realse bomb by the randomly choosen alien */
	void release_bomb();
	
	/* To remove the alien from vector after being hit by rocket and update the data structure */ 
	void update_alien_army_after_hit(Rocket *rocket, Player *player);
	
	/* To erase all elements of vector */
	void clear_alien_army_vect();
	
}__attribute__((aligned));

#endif

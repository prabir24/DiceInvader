#include "Bomb.h"

Bomb::Bomb(Engine *e)
{
	engine = e;
#ifndef VECTOR
	bomb_loc_vect = {0, {0}, {0}};
#endif
}

/*
Draw bomb on screen and store bomb co-ordinates to Vector data structure.
@param  - [ int, int ] : Randomly choosen Alien's co-ordinates
@return - None
*/
void Bomb::draw_bomb(int loc_x, int loc_y)
{
	engine->drawSprite(Engine::Sprite::Bomb, loc_x, loc_y);
#ifdef VECTOR
	bomb_loc_vect.push_back(std::make_pair(loc_x, loc_y));
#else
	bomb_loc_vect.x[bomb_loc_vect.size] = loc_x;
	bomb_loc_vect.y[bomb_loc_vect.size] = loc_y;
	bomb_loc_vect.size += 1;
#endif
}	

/*
Increment bomb's Y co-ordinate and uodate these changes to Vector data structure.
@param  - None
@return - None
*/
void Bomb::update_bomb_position()
{
#ifdef VECTOR
	for(int it=0; it < bomb_loc_vect.size(); it++)
		engine->drawSprite(Engine::Sprite::Bomb, bomb_loc_vect[it].first, bomb_loc_vect[it].second++);

	if((bomb_loc_vect.size() > 0) && (bomb_loc_vect[0].second >= Engine::CanvasHeight))
		bomb_loc_vect.erase(bomb_loc_vect.begin() + 0);
		
#else
	for(int it=0; it < bomb_loc_vect.size; it++)
		engine->drawSprite(Engine::Sprite::Bomb, bomb_loc_vect.x[it], bomb_loc_vect.y[it]++);
	
	if((bomb_loc_vect.size > 0) && (bomb_loc_vect.y[0] >= Engine::CanvasHeight))
		remove(0);

#endif	
}


#ifndef VECTOR
/*
It updates all the elements to the left of the index by 1 place and reduces size by 1. 
@param  - [ int ] : index of co-ordinates to be removed
@return - None
*/
void Bomb::remove(int loc)
{
	for(int it=loc; it < bomb_loc_vect.size; it++)
	{
		bomb_loc_vect.x[it] = bomb_loc_vect.x[it+1];
		bomb_loc_vect.y[it] = bomb_loc_vect.y[it+1];	
	}
	bomb_loc_vect.size -= 1;
}

#endif

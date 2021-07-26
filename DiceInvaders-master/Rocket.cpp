#include "Rocket.h"

Rocket::Rocket(Engine *e)
{
	engine = e;
#ifndef VECTOR
	rocket_loc_vect = {0, {0}, {0}};
#endif
}

/*	
To draw rocket sprite on Canvas and store the location co-ordinates in the Vector data structure.
@param  - [int, int] : X and Y co-ordinates of rocket location
@return - None
*/
void Rocket::draw_rocket(int loc_x, int loc_y)
{
	engine->drawSprite(Engine::Sprite::Rocket, loc_x , loc_y);
#ifdef VECTOR
	rocket_loc_vect.push_back(std::make_pair(loc_x, loc_y));
#else
	rocket_loc_vect.x[rocket_loc_vect.size] = loc_x;
	rocket_loc_vect.y[rocket_loc_vect.size] = loc_y;
	rocket_loc_vect.size += 1;
#endif
}	

/*
To decrement and update the location Y co-ordinates in Vector data structure.
Location co-ordinates are erased from Vector after Y co-ordinates value goes below 1/2 of SpriteSize.
@param  - None
@return - None
*/
void Rocket::update_rocket_position()
{
#ifdef VECTOR
	for(int it=0; it < rocket_loc_vect.size(); it++)
		engine->drawSprite(Engine::Sprite::Rocket, rocket_loc_vect[it].first, rocket_loc_vect[it].second--);
	
	if((rocket_loc_vect.size() > 0) && (rocket_loc_vect[0].second < Engine::SpriteSize/2))
		rocket_loc_vect.erase(rocket_loc_vect.begin() + 0);
		
#else
	for(int it=0; it < rocket_loc_vect.size; it++)
		engine->drawSprite(Engine::Sprite::Rocket, rocket_loc_vect.x[it], rocket_loc_vect.y[it]--);
	
	if((rocket_loc_vect.size > 0) && (rocket_loc_vect.y[0] < Engine::SpriteSize/2))
		remove(0);

#endif
}

#ifndef VECTOR
/*
It updates all the elements to the left of the index by 1 place and reduces size by 1. 
@param  - [ int ] : index of co-ordinates to be removed
@return - None
*/
void Rocket::remove(int loc)
{
	for(int it=loc; it < rocket_loc_vect.size; it++)
	{
		rocket_loc_vect.x[it] = rocket_loc_vect.x[it+1];
		rocket_loc_vect.y[it] = rocket_loc_vect.y[it+1];	
	}
	rocket_loc_vect.size -= 1;
}

#endif





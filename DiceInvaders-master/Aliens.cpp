#include <stdlib.h>
#include <time.h>
#include "Aliens.h"

Aliens::Aliens(Engine *e, Bomb *b)
{
	bomb					= b;
	engine					= e;
	is_left_direction		= true;
	has_reached_bottom		= false;
	has_direction_changed 	= false;
	all_aliens_killed		= false;
	alien_army_N_row		= 0;
	alien_army_N_col		= 0;
#ifndef VECTOR
	aliens_army_vect 		= {0, {0}, {0}, Engine::Sprite::Enemy1};
#endif
}

/*
Dram Alien army on screen with randomly choosen alien colour.
@param  - [ int, int] : No. of Rows of alien army, No. of Columns of alien army
@return - None
*/
void Aliens::draw_alien_army(int n_rows, int n_cols)
{
	srand(time(NULL));
	
	for(int row = 0; row < n_rows; row++)
	{
		//(2 *row) is to insert some gap between aliens.
		int loc_Y = (row * Engine::SpriteSize) + Engine::SpriteSize/2 + (2 * row); 

		for(int col = 0; col < n_cols; col++)
		{
    			int random_var = std::rand() % 2;	//choose radomly between 0 and 1
    			int loc_X = (col * Engine::SpriteSize) + (2 * col);

    			if(random_var == 0)
    			{
    				engine->drawSprite(Engine::Sprite::Enemy1, loc_X , loc_Y);
#ifdef VECTOR    				
    				aliens_army_vect.push_back(std::make_pair(Engine::Sprite::Enemy1, std::make_pair(loc_X, loc_Y)));
#else
				aliens_army_vect.x[aliens_army_vect.size] = loc_X;
				aliens_army_vect.y[aliens_army_vect.size] = loc_Y;
				aliens_army_vect.al[aliens_army_vect.size] = Engine::Sprite::Enemy1;
				aliens_army_vect.size += 1;
#endif
    			}
    			else if(random_var == 1)
    			{
    				engine->drawSprite(Engine::Sprite::Enemy2, loc_X , loc_Y);
#ifdef VECTOR
    				aliens_army_vect.push_back(std::make_pair(Engine::Sprite::Enemy2, std::make_pair(loc_X, loc_Y)));
#else
				aliens_army_vect.x[aliens_army_vect.size] = loc_X;
				aliens_army_vect.y[aliens_army_vect.size] = loc_Y;
				aliens_army_vect.al[aliens_army_vect.size] = Engine::Sprite::Enemy2;
				aliens_army_vect.size += 1;
#endif
    				
    			}
    		}
    	}
	
	is_left_direction		= true;
	has_reached_bottom		= false;
	has_direction_changed	= false;
	all_aliens_killed		= false;
}

/*
To update the alien army X co-ordinates after each move and store that in Vector data structure.
@param   - None
@return  - None
*/
void Aliens::update_alien_army_horizontal()
{
#ifdef VECTOR
	for(int it=0; it < aliens_army_vect.size(); it++)
	{
		if(is_left_direction)
			aliens_army_vect[it].second.first += Engine::SpriteSize + 2;	//2 is the gap between aliens
		else
			aliens_army_vect[it].second.first -= Engine::SpriteSize + 2;
	}
	
	/* To update the boolean variables based on rightmost/leftmost alien position */
	for(int it=0; it < aliens_army_vect.size(); it++)
	{
		if(aliens_army_vect[it].second.first >= (Engine::CanvasWidth - Engine::SpriteSize))
		{
			is_left_direction	= false;
			has_direction_changed	= true;
			break;
		}
		else if(aliens_army_vect[it].second.first <= 0)
		{
			is_left_direction	= true;
			has_direction_changed 	= true;
			break;
		}
	}
#else
	for(int it=0; it < aliens_army_vect.size; it++)
	{
		if(is_left_direction)
			aliens_army_vect.x[it] += Engine::SpriteSize + 2;	//2 is the gap between aliens
		else
			aliens_army_vect.x[it] -= Engine::SpriteSize + 2;
	}
	
	/* To update the boolean variables based on rightmost/leftmost alien position */
	for(int it=0; it < aliens_army_vect.size; it++)
	{
		if(aliens_army_vect.x[it] >= (Engine::CanvasWidth - Engine::SpriteSize))
		{
			is_left_direction	= false;
			has_direction_changed	= true;
			break;
		}
		else if(aliens_army_vect.x[it] <= 0)
		{
			is_left_direction	= true;
			has_direction_changed 	= true;
			break;
		}
	}
#endif
}

/*
To update the alien army Y co-ordinates after each downward move and store that in Vector data structure.
@param   - None
@return  - None
*/
void Aliens::update_alien_army_vertical()
{
	if(has_direction_changed)
	{
		has_direction_changed = false;

#ifdef VECTOR
		for(int it=0; it < aliens_army_vect.size(); it++)
			aliens_army_vect[it].second.second += Engine::SpriteSize + 2; //2 is the gap between aliens
#else
		for(int it=0; it < aliens_army_vect.size; it++)
			aliens_army_vect.y[it] += Engine::SpriteSize + 2; //2 is the gap between aliens
#endif
	}
}

/*
To refresh/redraw the alien army on screen.
@param   - None
@return  - None
*/
void Aliens::refresh_alien_army()
{
#ifdef VECTOR
	for(int it=0; it < aliens_army_vect.size(); it++)
		engine->drawSprite(aliens_army_vect[it].first, aliens_army_vect[it].second.first, aliens_army_vect[it].second.second);
#else
	for(int it=0; it < aliens_army_vect.size; it++)
		engine->drawSprite(aliens_army_vect.al[it], aliens_army_vect.x[it], aliens_army_vect.y[it]);
#endif	
}

/*
To check if any one of alien army has touch the bottom of screen (CanvasHeight).
@param   - None
@return  - None
*/
void Aliens::reached_bottom()
{
#ifdef VECTOR
	for(int it = aliens_army_vect.size()-1; it >= 0; it--)
	{
		if(aliens_army_vect[it].second.second > (Engine::CanvasHeight - Engine::SpriteSize))
#else
	for(int it = aliens_army_vect.size-1; it >= 0; it--)
	{
		if(aliens_army_vect.y[it] > (Engine::CanvasHeight - Engine::SpriteSize))
#endif
		{
			has_reached_bottom = true;
			break;
		}
	}
}

/*
Release bomb by the randoly choosen alien from alien army.
@param   - None
@return  - None
*/
void Aliens::release_bomb()
{
	srand(time(NULL));
#ifdef VECTOR
	if(aliens_army_vect.size() > 0)
	{
		int random_var = std::rand() % aliens_army_vect.size();	
		int loc_X = aliens_army_vect[random_var].second.first - Engine::SpriteSize/2;
		int loc_Y = aliens_army_vect[random_var].second.second + Engine::SpriteSize;
		bomb->draw_bomb(loc_X, loc_Y);
	}
#else
	if(aliens_army_vect.size > 0)
	{
		int random_var = std::rand() % aliens_army_vect.size;	
		int loc_X = aliens_army_vect.x[random_var] - Engine::SpriteSize/2;
		int loc_Y = aliens_army_vect.y[random_var] + Engine::SpriteSize;
		bomb->draw_bomb(loc_X, loc_Y);
	}
#endif
}

/*
To remove the alien from vector after being hit by rocket and update the data structure.
@param   - [ Pointer(Rocket), Pointer(Player)] : Rocket object, Player object
@return  - None
*/
			
void Aliens::update_alien_army_after_hit(Rocket *rocket, Player *player)
{
#ifdef VECTOR
	for(auto it_r = rocket->rocket_loc_vect.begin(); it_r != rocket->rocket_loc_vect.end(); ++it_r)
	{
		/* If rocket is above the top row of alien army, then no need to proceed further and continue to next rocket */
		if((it_r->second + Engine::SpriteSize) < aliens_army_vect[0].second.second) continue;
		
		/* If rocket is below bottom row of alien army, then no ned to check for other rockets and brek from the loop */
		if(it_r->second > (aliens_army_vect[aliens_army_vect.size() - 1].second.second + Engine::SpriteSize)) break;
		
		for(auto it_a = aliens_army_vect.begin(); it_a != aliens_army_vect.end(); ++it_a)
		{
			/* Check Rocket's area is inside Alien's area or not */
			/* Rocket's X-Boundary : [x1+(32/3)] - [x1+32-(32/3)] */
			/* Rocket's Y-Boundary : [y1+(32/3)] - [y1+32-(32/3)] */
			/* Alien's X-Boundary  : [x1] - [x1+32] */
			/* Alien's Y-Boundary  : [y1] - [y1+32] */
			/* SpriteSize = 32 */
			
			if( ((it_r->first  + Engine::SpriteSize/3) > it_a->second.first) &&
				((it_r->first  + Engine::SpriteSize - Engine::SpriteSize/3) <  (it_a->second.first + Engine::SpriteSize)) &&
				((it_r->second + Engine::SpriteSize/3) >  it_a->second.second) &&
				((it_r->second + Engine::SpriteSize - Engine::SpriteSize/3) <  (it_a->second.second + Engine::SpriteSize)) )
			{
				it_r = rocket->rocket_loc_vect.erase(it_r);
				it_a = aliens_army_vect.erase(it_a);
				
				player->score += 1;
				
				if(it_a == aliens_army_vect.end())
					break;
			}
		}
		if(it_r == rocket->rocket_loc_vect.end())
					break;
	}
	if(aliens_army_vect.size() == 0)
		all_aliens_killed = true;

#else
	for(auto it_r = 0; it_r < rocket->rocket_loc_vect.size; ++it_r)
	{
		if((rocket->rocket_loc_vect.y[it_r] + Engine::SpriteSize) < aliens_army_vect.y[0]) continue;
		
		if(rocket->rocket_loc_vect.y[it_r] > (aliens_army_vect.y[aliens_army_vect.size - 1] + Engine::SpriteSize)) break;
		
		for(auto it_a = 0; it_a < aliens_army_vect.size; ++it_a)
		{
			/* Check Rocket's area is inside Alien's area or not */
			/* Rocket's X-Boundary : [x1+(32/3)] - [x1+32-(32/3)] */
			/* Rocket's Y-Boundary : [y1+(32/3)] - [y1+32-(32/3)] */
			/* Alien's X-Boundary  : [x1] - [x1+32] */
			/* Alien's Y-Boundary  : [y1] - [y1+32] */
			/* SpriteSize = 32 */
			
			if( ((rocket->rocket_loc_vect.x[it_r]  + Engine::SpriteSize/3) > aliens_army_vect.x[it_a]) &&
				((rocket->rocket_loc_vect.x[it_r]  + Engine::SpriteSize - Engine::SpriteSize/3) <  (aliens_army_vect.x[it_a] + Engine::SpriteSize)) &&
				((rocket->rocket_loc_vect.y[it_r] + Engine::SpriteSize/3) >  aliens_army_vect.y[it_a]) &&
				((rocket->rocket_loc_vect.y[it_r] + Engine::SpriteSize - Engine::SpriteSize/3) <  (aliens_army_vect.y[it_a] + Engine::SpriteSize)) )
			{
				rocket->remove(it_r);
				remove(it_a);
				
				player->score += 1;
			}
		}
	}
	if(aliens_army_vect.size == 0)
		all_aliens_killed = true;
#endif		
}

/*
To erase all elements in aliens army vector data structure.
@param  - None
@return  - None
*/
void Aliens::clear_alien_army_vect()
{
#ifdef VECTOR
	aliens_army_vect.clear();
#else
	aliens_army_vect = {0, {0}, {0}, Engine::Sprite::Enemy1};
#endif
}

#ifndef VECTOR
/*
It updates all the elements to the left of the index by 1 place and reduces size by 1. 
@param  - [ int ] : index of co-ordinates to be removed
@return - None
*/
void Aliens::remove(int loc)
{
	for(int it=loc; it < aliens_army_vect.size; it++)
	{
		aliens_army_vect.x[it] = aliens_army_vect.x[it+1];
		aliens_army_vect.y[it] = aliens_army_vect.y[it+1];
		aliens_army_vect.al[it] = aliens_army_vect.al[it+1];	
	}
	aliens_army_vect.size -= 1;
}

#endif

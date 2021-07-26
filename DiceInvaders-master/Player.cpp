#include "Player.h"
#include "Rocket.h"
#include "Bomb.h"

Player::Player(Engine *e)
{
	engine	=	e;
	score	=	0;
	life	=	3;
}

/*
Update player location based on input's from user.
@param  - [ int ] : Player's X co-ordinate
@return - None
*/
void Player::update_player_location(int loc_x)
{
	engine->drawSprite(Engine::Sprite::Player, loc_x , (Engine::CanvasHeight - Engine::SpriteSize));
}

/*
Display score on top left corner (0,0) of screen.
@param  - None
@return - None
*/
void Player::display_score()
{
	std::string message = "Score : " + std::to_string(score);
	const char *msg = message.c_str();
	engine->drawText(msg, 0, 0);
}

/*
Decrement Player's life if bomb touches the player.
@param  - [ Pointer(Bomb), int ] : Pointer to Bomb object, Player's X co-ordinates
@return - None
*/
void Player::update_player_life(Bomb *bomb, int player_loc)
{
	/* Bomb's Area inside Player's Area or not */
	/* Bomb's X-Boundary    : [x1] - [x1+32] */
	/* Bomb's Y-Boundary    : [y1] - [y1+32] */
	/* Player's X-Boundary  : [x1-(32/2)] - [x1+32+(32/2)] */
	/* Player's Y-Boundary  : [CanvasHeight-32-(32/2)] - [CanvasHeight] */
	/* SpriteSize = 32 */

#ifdef VECTOR		
	if( bomb->bomb_loc_vect.size() > 0 && 
		(bomb->bomb_loc_vect[0].first > (player_loc - Engine::SpriteSize/2)) &&
		((bomb->bomb_loc_vect[0].first + Engine::SpriteSize) <  (player_loc + Engine::SpriteSize + Engine::SpriteSize/2)) &&
		(bomb->bomb_loc_vect[0].second  >  (Engine::CanvasHeight - Engine::SpriteSize - Engine::SpriteSize/2)) &&
		((bomb->bomb_loc_vect[0].second + Engine::SpriteSize) <  Engine::CanvasHeight) )
	{		
		life -= 1;			
		bomb->bomb_loc_vect.erase(bomb->bomb_loc_vect.begin() + 0);
	}
#else
	if( bomb->bomb_loc_vect.size > 0 && 
		(bomb->bomb_loc_vect.x[0] > (player_loc - Engine::SpriteSize/2)) &&
		((bomb->bomb_loc_vect.x[0] + Engine::SpriteSize) <  (player_loc + Engine::SpriteSize + Engine::SpriteSize/2)) &&
		(bomb->bomb_loc_vect.y[0]  >  (Engine::CanvasHeight - Engine::SpriteSize - Engine::SpriteSize/2)) &&
		((bomb->bomb_loc_vect.y[0] + Engine::SpriteSize) <  Engine::CanvasHeight) )
	{		
		life -= 1;			
		bomb->remove(0);
	}
#endif
}

/*
Display player's life on top right corner of screen.
@param  - None
@return - None
*/
void Player::display_life()
{
	std::string message = "Life : " + std::to_string(life);
	const char *msg = message.c_str();
	engine->drawText(msg, (Engine::CanvasWidth - (strlen(msg)  * Engine::FontWidth)), 0);
}

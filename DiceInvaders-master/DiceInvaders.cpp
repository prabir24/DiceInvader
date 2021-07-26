#include "Engine.h"
#include "Player.h"
#include "Rocket.h"
#include "Aliens.h"

void EngineMain()
{
	/* Objects of all the required classes */
	Engine engine;
	Player player(&engine);
	Rocket rocket(&engine);
	Bomb bomb(&engine);
	Aliens alien(&engine, &bomb);
	
	/* variables to manage the size of alien army */
	int n_alien_army_rows = 6;
	int n_alien_army_cols = 12;
	
	/* variable for Player location on x-axis */
	int player_loc = (Engine::CanvasWidth - Engine::SpriteSize) / 2;
	
	/* Variable to check fire key pressed or released */
	bool is_fire_key_pressed = false;
	
	/* Variable to store or count time elapsed */
	long prev_timestamp;
	long curr_timestamp = 0;
	int time_elapsed_in_sec = -1;
	int curr_time = 0;
	
	/* To store prev player life count */
	int prev_life_count = 0;

	/* To check player killed by bomb or not */
	bool player_killed_flag = false;
	
	/* To check if user want to start the game or not */
	bool start_game_flag = false;


	/************************************************************************************************************/
	/*						Welcome Screen							*/
	/************************************************************************************************************/
	
	
	/* Inital screen display game rules and other info */
	while (engine.startFrame())
	{
		player.display_score();
		player.display_life();
		
		player.update_player_location(player_loc);
		alien.draw_alien_army(4, n_alien_army_cols);
#ifndef VECTOR
		alien.clear_alien_army_vect();
#endif 
		
		const char msg1[] = "WELCOME TO DICE INVADERS GAME";
		engine.drawText(msg1, (Engine::CanvasWidth - ((sizeof(msg1) - 1) * Engine::FontWidth))/2, (Engine::CanvasHeight - Engine::FontRowHeight)/2);
		
		const char msg2[] = "Use ARROW LEFT/RIGHT to move player and SPACE to fire rockets";
		engine.drawText(msg2, (Engine::CanvasWidth - ((sizeof(msg2) - 1) * Engine::FontWidth))/2, (Engine::CanvasHeight - Engine::FontRowHeight + (4 * Engine::FontRowHeight))/2);
		
		const char msg3[] = "Press SPACE to start the game";
		engine.drawText(msg3, (Engine::CanvasWidth - ((sizeof(msg3) - 1) * Engine::FontWidth))/2, (Engine::CanvasHeight - Engine::FontRowHeight + (8 * Engine::FontRowHeight))/2);
		
		Engine::PlayerInput keys = engine.getPlayerInput();
		if(keys.fire)
		{
			start_game_flag = true;
			alien.clear_alien_army_vect();
			break;
		}
	}	
	
	if(!start_game_flag)
		return;
		
		
	/************************************************************************************************************/
	/*						Game Screen							*/
	/************************************************************************************************************/
	
		
	while (engine.startFrame())
	{
		prev_life_count = player.life;
		prev_timestamp = curr_timestamp;
		curr_timestamp = (long)engine.getStopwatchElapsedSeconds();
		
		/* Display Score and Player's life available on screen */
		player.display_score();
		player.display_life();

		/* Draw alien army only when prev_timestamp is 0 */
		if(prev_timestamp == 0)
			alien.draw_alien_army(n_alien_army_rows, n_alien_army_cols);
	
		/* Alien movement and bomb release are triggered after every second  */		
		if(prev_timestamp != curr_timestamp)
		{
			time_elapsed_in_sec += 1;

			if(alien.has_direction_changed)
				alien.update_alien_army_vertical();
			else
				alien.update_alien_army_horizontal();
			
			/* Initially 1st Bomb will be triggered after 3 sec. 
			There after each second, bomb release will be triggered from one of alien randomly */
			if(time_elapsed_in_sec >= 3)
				alien.release_bomb();
					
			alien.reached_bottom();
		}
		
		/* User input for player left/right movement*/	
		Engine::PlayerInput keys = engine.getPlayerInput();
		if (keys.left)
		{
			--player_loc;
			if(player_loc < (~(Engine::SpriteSize) + 1))
				player_loc = (~(Engine::SpriteSize) + 1);
		}
		if (keys.right)
		{
			++player_loc;
			if(player_loc > Engine::CanvasWidth)
				player_loc = Engine::CanvasWidth;
		}

		/* Update player location based on user input */
		player.update_player_location(player_loc);
		
		/* User input for Fire Rockets */
		if(keys.fire && !is_fire_key_pressed)
		{
			is_fire_key_pressed = true;
			rocket.draw_rocket(player_loc, (Engine::CanvasHeight - Engine::SpriteSize));
		}
		else if(!keys.fire)
			is_fire_key_pressed = false;
		
		/* Update player life if bomb hit player */
		player.update_player_life(&bomb, player_loc);

		/* Trace and update bomb downward movement */
		bomb.update_bomb_position();
		
		/* If player life count decrements than adjust player's location to initial position and raise req. flag */
		if(prev_life_count != player.life)
		{
			player_loc = (Engine::CanvasWidth - Engine::SpriteSize) / 2;
			player_killed_flag = true;
			curr_time = time_elapsed_in_sec;
		}
		
		/* Alien army update after hit a rocket and also remove rocket from vector that hits alien */
		alien.update_alien_army_after_hit(&rocket, &player);
		alien.refresh_alien_army();
		rocket.update_rocket_position();
		
		/* Display some text for 2 seconds if Player is killed by a bomb */
		if(player_killed_flag && (time_elapsed_in_sec < (curr_time + 2)))
			engine.drawText("Bombed" , player_loc, (Engine::CanvasHeight - (2 * Engine::SpriteSize)));
		else if(player_killed_flag)
			player_killed_flag = false;
		
		/* If all aliens in the army are killed, reset curr_timestamp and time elapsed variable */
		if(alien.all_aliens_killed)
		{
			time_elapsed_in_sec = 0;
			curr_timestamp = 0;	
		}
		
		/* If one of alien army reached bottom of screen, then it breaks from loop and game is over */ 
		if((player.life == 0) || alien.has_reached_bottom)
			break;	
	}
	
	
	/************************************************************************************************************/
	/*						End Screen							*/
	/************************************************************************************************************/
	
	
	/* Freeze the last scrren when game is over i.e. either player life is 0 or alien reached bottom */
	while ((alien.has_reached_bottom || (player.life == 0)) && engine.startFrame())
	{
		player.display_score();
		player.display_life();
		
		/* Display game over state of screen */
		player.update_player_location(player_loc);
		rocket.update_rocket_position();
		alien.refresh_alien_army();
		
		const char msg[] = "GAME OVER";
		engine.drawText(msg, (Engine::CanvasWidth - (sizeof(msg)  * Engine::FontWidth))/2, (Engine::CanvasHeight - Engine::FontRowHeight)/2);
	}
}


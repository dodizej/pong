#include<Windows.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <string>
#include <math.h>
#include <memory.h>
#include "Display.h"
#include "Racket.h"
#include "Input.h"
#include "KeyboardInput.h"
#include "Ball.h"
#include "PlayerRacket.h"
#include "ComputerRacket.h"
#include "Menu.h"


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	SDL_Event evt;
	bool exit = false;

	int game_status = 0;

	int window_size_x = 900;
	int window_size_y = 700;

	std::shared_ptr<Input> input_ptr(new KeyboardInput());

	std::shared_ptr<Display> display_ptr = Display::get_instance(window_size_x, window_size_y);




	// Menu

	/*
	std::shared_ptr<Menu> menu_ptr = Menu::get_instance(display_ptr);

	input_ptr->add_listener(menu_ptr);

	while (!exit)
	{
		display_ptr->clear();
		int status = input_ptr->check_input();
		if (status != 0)
		{
			exit = true;
			break;
		}
		menu_ptr->show();
		display_ptr->show();
	}
	*/
 
	// Game

	bool computers = true;

	// Create objects
	std::shared_ptr<Ball> ball_ptr(new Ball(display_ptr, window_size_x / 2, window_size_y / 2));


	//std::shared_ptr<PlayerRacket>   player_racket_ptr(new PlayerRacket(display_ptr, 50, window_size_y / 2));
	std::shared_ptr<ComputerRacket> computer_racket_ptr1(new ComputerRacket(display_ptr, 50, window_size_y / 2, ball_ptr));
	std::shared_ptr<ComputerRacket> computer_racket_ptr2(new ComputerRacket(display_ptr, window_size_x - 50, window_size_y / 2, ball_ptr));

	// Add player racket as listener to keyboard input
	//input_ptr->add_listener(player_racket_ptr);

	// Add collision objects
	ball_ptr->add_collision_obj(computer_racket_ptr1);
	ball_ptr->add_collision_obj(computer_racket_ptr2);


	std::vector<std::shared_ptr<Object>> objects;
	objects.push_back(ball_ptr);
	//objects.push_back(player_racket_ptr);
	objects.push_back(computer_racket_ptr1);
	objects.push_back(computer_racket_ptr2);

	int player_points = 0;
	int computer_points = 0;

	while (!exit)
	{
		display_ptr->clear();
		input_ptr->check_input();
		for (std::vector<std::shared_ptr<Object>>::iterator it = objects.begin(); it < objects.end(); ++it)
		{
			(*it)->draw();
		}
		display_ptr->show();

		game_status = ball_ptr->get_game_status();
		if (game_status != 0)
		{
			if (game_status > 0)
			{
				++computer_points;
				SDL_Log("Computer +1");
			}
			else
			{
				++player_points;
				SDL_Log("Player +1");
			}

			if (player_points >= 10 || computer_points >= 10)
			{
				if (player_points >= 3)
				{
					display_ptr->draw_text("Player won!", window_size_x/2, window_size_y*0.2);
					SDL_Log("Player won!");
					display_ptr->show();
					break;
				}
				else if (computer_points == 3)
				{
					display_ptr->draw_text("Computer won!", window_size_x / 2, window_size_y * 0.2);
					SDL_Log("Computer won!");
					display_ptr->show();
					break;
				}

			}

			for (std::vector<std::shared_ptr<Object>>::iterator it = objects.begin(); it < objects.end(); ++it)
			{
				(*it)->reset_position();
			}
			SDL_Delay(200);
		}
	}

	while (!exit)
	{
		while (SDL_PollEvent(&evt))
		{
			if (evt.type == SDL_QUIT)
			{
				exit = true;
			}
		}
	}

	return 0;
}

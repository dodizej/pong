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


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{

	int game_status = 0;

	std::shared_ptr<Display> display_ptr = Display::get_instance(700, 500);

	std::shared_ptr<Input>   input_ptr(new KeyboardInput());


	std::shared_ptr<PlayerRacket> racket_ptr(new PlayerRacket(display_ptr, 50, 50));
	std::shared_ptr<Ball>         ball_ptr(new Ball(display_ptr, 100, 100));

	ball_ptr->add_collision_obj(racket_ptr);


	std::vector<std::shared_ptr<Object>> objects;
	objects.push_back(racket_ptr);
	objects.push_back(ball_ptr);


	input_ptr->add_listener(racket_ptr);


	SDL_Event evt;
	bool exit = false;
	while (!exit)
	{
		while (!exit && ball_ptr->get_game_status() <= 0)
		{
			//racket_ptr->x += 5;
			display_ptr->clear();
			int status = input_ptr->check_input();
			if (status < 0)
			{
				exit = true;
				break;
			}
			for (std::vector<std::shared_ptr<Object>>::iterator it = objects.begin(); it < objects.end(); ++it)
			{
				(*it)->draw();
			}
			display_ptr->show();
		}

		if (ball_ptr->get_game_status() > 0)
		{
			SDL_Log("+1 point for Player 2 ");
			break;
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

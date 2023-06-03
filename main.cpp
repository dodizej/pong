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


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{

	std::shared_ptr<Display> display_ptr = Display::get_instance(1000, 700);

	std::shared_ptr<Input>   input_ptr(new KeyboardInput());


	std::shared_ptr<Racket>  racket_ptr(new Racket(display_ptr, 50, 50));
	std::shared_ptr<Ball>    ball_ptr(new Ball(display_ptr, 100, 50));


	std::vector<std::shared_ptr<Object>> objects;
	objects.push_back(racket_ptr);
	objects.push_back(ball_ptr);


	input_ptr->addListener(racket_ptr);


	SDL_Event evt;
	bool exit = false;
	while (!exit)
	{
		//racket_ptr->x += 5;
		display_ptr->clear();
		int status = input_ptr->check_input();
		if (status < 0)
		{
			exit = true;
		}
		for (std::vector<std::shared_ptr<Object>>::iterator it = objects.begin(); it < objects.end(); ++it)
		{
			(*it)->draw();
		}
		display_ptr->show();
	}

	return 0;

	// returns zero on success else non-zero
	
	/*
	int window_size_x = 1200;
	int window_size_y = 700;

	SDL_Window* win = SDL_CreateWindow("Pong", // creates a window
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_size_x, window_size_y, 0);

	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	SDL_Renderer* m_window_renderer = SDL_CreateRenderer(win, -1, render_flags);

	SDL_RenderClear(m_window_renderer);

	SDL_Rect rect;
	rect.x = 50;
	rect.y = 50;
	rect.w = 20;
	rect.h = 70;

	SDL_SetRenderDrawColor(m_window_renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(m_window_renderer, &rect);


	SDL_RenderPresent(m_window_renderer);

	int ball_speed = 5;
	int speed = 10;
	int velocity_x = 0;
	int velocity_y = 0;

	SDL_Event evt;
	bool exit = false;
	int i = 0;
	while (!exit) {

		while (SDL_PollEvent(&evt)) {

			if (evt.type == SDL_KEYDOWN)
			{
				if (evt.key.keysym.scancode == SDL_SCANCODE_UP)
				{
					velocity_y = -1;
				}
				else if (evt.key.keysym.scancode == SDL_SCANCODE_DOWN)
				{
					velocity_y = 1;
				}
				else if (evt.key.keysym.scancode == SDL_SCANCODE_LEFT)
				{
					velocity_x = -1;
				}
				else if (evt.key.keysym.scancode == SDL_SCANCODE_RIGHT)
				{
					velocity_x = 1;
				}
			}

			if (evt.type == SDL_KEYUP)
			{
				if (evt.key.keysym.scancode == SDL_SCANCODE_UP && velocity_y == -1)
				{
					velocity_y = 0;
				}
				else if (evt.key.keysym.scancode == SDL_SCANCODE_DOWN && velocity_y == 1)
				{
					velocity_y = 0;
				}
				else if (evt.key.keysym.scancode == SDL_SCANCODE_LEFT && velocity_x == -1)
				{
					velocity_x = 0;
				}
				else if (evt.key.keysym.scancode == SDL_SCANCODE_RIGHT && velocity_x == 1)
				{
					velocity_x = 0;
				}
			}

			if (evt.type == SDL_QUIT)
			{
				exit = true;
			}

		}

		//rect.x += speed * velocity_x;
		rect.y += speed * velocity_y;


		// right boundary
		if (rect.x + rect.w > window_size_x)
		{
			velocity_x = 0;
			rect.x = window_size_x - rect.w;
		}
		// left boundary
		if (rect.x < 0)
		{
			velocity_x = 0;
			rect.x = 0;
		}
		// bottom boundary
		if (rect.y + rect.h > window_size_y)
		{
			velocity_y = 0;
			rect.y = window_size_y - rect.h;
		}
		// upper boundary
		if (rect.y < 0)
		{
			velocity_y = 0;
			rect.y = 0;
		}

		// clears the screen
		SDL_RenderClear(m_window_renderer);

		SDL_SetRenderDrawColor(m_window_renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(m_window_renderer, &rect);
		SDL_RenderFillRect(m_window_renderer, &rect);
		SDL_SetRenderDrawColor(m_window_renderer, 0, 0, 0, 255);

		// triggers the double buffers
		// for multiple rendering
		SDL_RenderPresent(m_window_renderer);

		SDL_Delay(1000 / 60);  // 60 fps

	}
	*/
}

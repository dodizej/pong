#include "Display.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

Display::Display(int window_size_x, int window_size_y)
{
	this->window_size_x = window_size_x;
	this->window_size_y = window_size_y;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}

	this->win = SDL_CreateWindow(
		  "Pong"
		, SDL_WINDOWPOS_CENTERED
		, SDL_WINDOWPOS_CENTERED
		, window_size_x
		, window_size_y
		, 0
	);

	this->render_flags = SDL_RENDERER_ACCELERATED;

	this->m_window_renderer = SDL_CreateRenderer(win, -1, render_flags);
	SDL_SetRenderDrawColor(m_window_renderer, 0, 0, 0, 255);

	
}

std::shared_ptr<Display> Display::get_instance(int window_size_x, int window_size_y)
{
	static std::shared_ptr<Display> display_ptr(new Display(window_size_x, window_size_y));
    return display_ptr;
}


void Display::drawRect(int x, int y, int w, int h)
{
	SDL_Rect rect; // always creating a new object
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	
	SDL_SetRenderDrawColor(this->m_window_renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(this->m_window_renderer, &rect);
}

void Display::clear()
{
	SDL_RenderClear(m_window_renderer);
}

void Display::show()
{
	SDL_RenderPresent(m_window_renderer);
}

void Display::get_window_size(int & x, int & y)
{
	x = this->window_size_x;
	y = this->window_size_y;
}

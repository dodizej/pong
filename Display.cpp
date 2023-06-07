#include <iostream>
#include "Display.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>


Display::Display(int window_size_x, int window_size_y)
{
	this->window_size_x = window_size_x;
	this->window_size_y = window_size_y;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}

	TTF_Init();

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
	static std::shared_ptr<Display> display_ptr = std::make_shared<Display>(Display(window_size_x, window_size_y));
    return display_ptr;
}

void Display::draw_rect_empty(int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_SetRenderDrawColor(this->m_window_renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(this->m_window_renderer, &rect);
	SDL_SetRenderDrawColor(this->m_window_renderer, 0, 0, 0, 255);
}

void Display::draw_rect(int x, int y, int w, int h)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	
	SDL_SetRenderDrawColor(this->m_window_renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(this->m_window_renderer, &rect);
	SDL_SetRenderDrawColor(this->m_window_renderer, 0, 0, 0, 255);
}

TTF_Font* Display::get_font(int font_size)
{
	if (fonts_by_size.find(font_size) == fonts_by_size.end())
	{
		TTF_Font* font_ptr = TTF_OpenFont("C:\\WINDOWS\\FONTS\\arial.ttf", font_size);  // find font on OS or ship with game ?
		if (!font_ptr) {
			SDL_Log("Error loading font: ");
			SDL_Log(TTF_GetError());
			return NULL;
		}
		fonts_by_size[font_size] = font_ptr;
	}
	return fonts_by_size[font_size];
}

void Display::draw_text(std::string text, int x, int y, int font_size)
{
	TTF_Font* font_ptr = get_font(font_size);

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font_ptr, text.c_str(), {255, 255, 255});
	SDL_Texture* Message        = SDL_CreateTextureFromSurface(m_window_renderer, surfaceMessage);

	SDL_Rect Message_rect;  // little above center of the screen:
	Message_rect.x = x;     //   (window_size_x / 2) - (Message_rect.w / 2);
	Message_rect.y = y;     //   (window_size_y / 2) - (Message_rect.h / 2) - (window_size_y * 0.35);

	TTF_SizeText(font_ptr, text.c_str(), &Message_rect.w, &Message_rect.h);

	/*
	SDL_Log(std::to_string(Message_rect.x).c_str());
	SDL_Log(std::to_string(Message_rect.y).c_str());
	SDL_Log(std::to_string(Message_rect.w).c_str());
	SDL_Log(std::to_string(Message_rect.h).c_str());
	*/

	SDL_RenderCopy(m_window_renderer, Message, NULL, &Message_rect);
}

void Display::get_text_size(std::string text, int font_size, int & width, int & height)
{
	TTF_SizeText(get_font(font_size), text.c_str(), &width, &height);
}

void Display::clear()
{
	SDL_RenderClear(m_window_renderer);
}

void Display::show()
{
	SDL_RenderPresent(m_window_renderer);
	SDL_Delay(1000 / 60);
}

int Display::get_window_size_x()
{
	return this->window_size_x;
}

int Display::get_window_size_y()
{
	return this->window_size_y;
}

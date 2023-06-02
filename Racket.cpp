#include "Racket.h"
#include <SDL2/SDL_rect.h>


Racket::Racket(std::shared_ptr<Display> _display_ptr, int x, int y) : Object(_display_ptr)
{
	this->x = x;
	this->y = y;
}

void Racket::draw()
{
	this->display_ptr->drawRect(x, y, width, height);
}


void Racket::buttonPressed(Key k)
{
	if (k == Key::UP)
	{
		velocity_y = -1;
	}
	else if (k == Key::DOWN)
	{
		velocity_y = 1;
	}
	else if (k == Key::LEFT)
	{
		velocity_x = -1;
	}
	else if (k == Key::RIGHT)
	{
		velocity_x = 1;
	}
	this->update_position();
}

void Racket::buttonReleased(Key k)
{
	if (k == Key::UP && velocity_y == -1)
	{
		velocity_y = 0;
	}
	else if (k == Key::DOWN && velocity_y == 1)
	{
		velocity_y = 0;
	}
	else if (k == Key::LEFT && velocity_x == -1)
	{
		velocity_x = 0;
	}
	else if (k == Key::RIGHT && velocity_x == 1)
	{
		velocity_x = 0;
	}
	this->update_position();
}

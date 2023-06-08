#include "Racket.h"

Racket::Racket(std::shared_ptr<Display> _display_ptr, int x, int y) : Object(_display_ptr, x, y)
{
	this->width  = 20;
	this->height = 90;
	this->speed  = 15;
}

void Racket::draw()
{
	this->display_ptr->draw_rect(x, y, width, height);
}

void Racket::update_position()
{

	// x += speed * velocity_x; // only y vertical movement
	y += speed * velocity_y;

	// right boundary
	if (x + width > window_size_x)
	{
		velocity_x = 0;
		x = window_size_x - width;
	}
	// left boundary
	if (x < 0)
	{
		velocity_x = 0;
		x = 0;
	}
	// bottom boundary
	if (y + height > window_size_y)
	{
		velocity_y = 0;
		y = window_size_y - height;
	}
	// upper boundary
	if (y < 0)
	{
		velocity_y = 0;
		y = 0;
	}

}

Racket::~Racket() { }

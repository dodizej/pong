#include "ComputerRacket.h"

ComputerRacket::ComputerRacket
(
	  std::shared_ptr<Display> display_ptr
	, int x
	, int y
	, std::shared_ptr<Ball> ball_ptr) : Racket(display_ptr, x, y)
{
	this->ball_ptr = ball_ptr;
}


void ComputerRacket::update_position()
{
	//velocity_y = 1;
	/*
	if (y < ball_ptr->get_y())
	{
		velocity_y = 1;
	}
	else if (y > ball_ptr->get_y())
	{
		velocity_y = -1;
	}
	else
	{
		//velocity_y = 0;
	}*/

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
		velocity_y = -1;
		y = window_size_y - height;
	}
	// upper boundary
	if (y < 0)
	{
		velocity_y = 1;
		y = 0;
	}

}
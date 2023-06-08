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

	int limit = rand() % 15 + 5;
	++frames;
	if (frames > limit)
	{
		int ball_y_velocity = ball_ptr->get_velocity_y();

		int x_ball_pos = ball_ptr->get_x() + (ball_ptr->get_w() / 2);
		int y_ball_pos = ball_ptr->get_y() + (ball_ptr->get_h() / 2);

		int x_diff = x + (width / 2) - x_ball_pos;
		int y_diff = y + (height / 2) - y_ball_pos;

		if (y_diff < -35)
		{
			velocity_y = 1;
		}
		else if (y_diff > 35)
		{
			velocity_y = -1;
		}
		else
		{
			velocity_y = 0;
		}
		frames = 0;
	}

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
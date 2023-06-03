#include "PlayerRacket.h"


PlayerRacket::PlayerRacket(std::shared_ptr<Display> _display_ptr, int x, int y) : Racket(_display_ptr, x, y)
{

}

void PlayerRacket::button_pressed(Key k)
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
}

void PlayerRacket::button_released(Key k)
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
}
